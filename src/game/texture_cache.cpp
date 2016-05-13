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

  SDL_Surface *image;
  SDL_RWops *rwop;
  rwop=SDL_RWFromFile(path.c_str(), "rb");
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
  image = loadFunc(rwop);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::get(), image);
  return cacheByPath.insert(std::make_pair(path, std::shared_ptr<Texture>(new Texture(texture)))).first->second;
}