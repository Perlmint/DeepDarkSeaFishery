#pragma once

#include <memory>

#include "util.h"

struct SDL_Texture;

class Texture : public std::enable_shared_from_this<Texture>
{
public:
  Texture() = delete;
  Texture(SDL_Texture *t);
  ~Texture();

  SDL_Texture *getTexture() { return _texture; }
  const Size &size() { return _size; }
private:
  SDL_Texture *_texture;
  Size _size;
};
