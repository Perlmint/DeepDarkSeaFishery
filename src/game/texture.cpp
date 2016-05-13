#include "texture.h"

#include <SDL2/SDL.h>

Texture::Texture(SDL_Texture *t)
  : _texture(t)
{
  int w, h;
  SDL_QueryTexture(t, nullptr, nullptr, &w, &h);
  _size.width = w;
  _size.height = h;
}

Texture::~Texture()
{
  SDL_DestroyTexture(_texture);
}