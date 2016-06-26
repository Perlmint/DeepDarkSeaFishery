#pragma once

#include <memory>
#include <map>

class Texture;
struct SDL_RWops;

class TextureCache : public std::enable_shared_from_this<TextureCache>
{
public:
  static std::weak_ptr<TextureCache> Instance();
  static void ReleaseInstance();
  std::weak_ptr<Texture> loadFromPath(const std::string &path);
#ifdef _MSC_VER
  std::weak_ptr<Texture> loadFromID(unsigned int id);
#endif

private:
  bool invalidated = false;
  std::map<std::string, std::shared_ptr<Texture> > cacheByPath;
  static std::shared_ptr<TextureCache> instance;
  std::shared_ptr<Texture> loadFromData(const char * const data, size_t size);
  std::shared_ptr<Texture> loadFromOps(SDL_RWops *op);
};