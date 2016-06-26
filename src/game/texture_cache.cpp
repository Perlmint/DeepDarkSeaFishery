#include "texture_cache.h"

#include <string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "texture.h"
#include "renderer.h"

std::shared_ptr<TextureCache> TextureCache::instance = nullptr;

#define IS_VALID()

std::weak_ptr<TextureCache> TextureCache::Instance()
{
  if (instance == nullptr)
  {
    instance.reset(new TextureCache());
  }
  
  return instance;
}

void TextureCache::ReleaseInstance()
{
  if (instance == nullptr)
  {
    return;
  }

  instance->invalidated = true;
  instance.reset();
  instance = nullptr;
}

std::weak_ptr<Texture> TextureCache::loadFromPath(const std::string &path)
{
  auto found = cacheByPath.find(path);
  if (found != cacheByPath.end())
  {
    return found->second;
  }

  SDL_RWops *rwop = SDL_RWFromFile(path.c_str(), "rb");

  return cacheByPath.insert(std::make_pair(path, loadFromOps(rwop))).first->second;
}

std::shared_ptr<Texture> TextureCache::loadFromData(const char * const data, size_t size)
{
  auto ret = loadFromOps(SDL_RWFromConstMem(data, static_cast<int>(size)));
  return ret;
}

#ifdef _MSC_VER
#include <Windows.h>
#include "res_map.h"
std::weak_ptr<Texture> TextureCache::loadFromID(unsigned int id)
{
  const auto &info = res_map.at(id);

  auto found = cacheByPath.find(info.path);
  if (found != cacheByPath.end())
  {
    return found->second;
  }

  HMODULE hModule = GetModuleHandle(NULL);

  HRSRC hImage = FindResource(hModule, MAKEINTRESOURCE(id), info.cat);
  unsigned int size = SizeofResource(hModule, hImage);
  HGLOBAL hg = LoadResource(hModule, hImage);
  const char* data = (const char*)LockResource(hg);
  auto ret = loadFromData(data, size);
  return cacheByPath.insert(std::make_pair(info.path, ret)).first->second;
}
#endif // _MSC_VER

std::shared_ptr<Texture> TextureCache::loadFromOps(SDL_RWops * rwop)
{
  SDL_Surface *(*loadFunc)(SDL_RWops *) = nullptr;
  if (IMG_isPNG(rwop))
  {
    loadFunc = &IMG_LoadPNG_RW;
  }
  else if (IMG_isBMP(rwop))
  {
    loadFunc = &IMG_LoadBMP_RW;
  }
  else if (IMG_isJPG(rwop))
  {
    loadFunc = &IMG_LoadJPG_RW;
  }
  else if (IMG_isGIF(rwop))
  {
    loadFunc = &IMG_LoadGIF_RW;
  }
  SDL_Surface *image = loadFunc(rwop);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::get(), image);
  return std::shared_ptr<Texture>(new Texture(texture));
}
