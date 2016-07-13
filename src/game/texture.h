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

  bool operator==(const Texture &t) const { return t._texture == _texture && t._size == _size; }
  SDL_Texture *getTexture() { return _texture; }
  const Size &size() { return _size; }
  size_t getHash() const;
private:
  SDL_Texture *_texture;
  Size _size;
};