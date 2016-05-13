#pragma once

#include <memory>
#include <map>

class Texture;

class TextureCache : public std::enable_shared_from_this<TextureCache>
{
public:
  static std::weak_ptr<TextureCache> Instance();
  static void ReleaseInstance();
  std::weak_ptr<Texture> loadFromPath(const std::string &path);

private:
  bool invalidated = false;
  std::map<std::string, std::shared_ptr<Texture> > cacheByPath;
  static std::shared_ptr<TextureCache> instance;
};