#include "util.h"

#include <SDL2/SDL.h>

void Point::toSDLRect(SDL_Rect &rect) const
{
  rect.x = x;
  rect.y = y;
}

void Size::toSDLRect(SDL_Rect &rect) const
{
  rect.w = width;
  rect.h = height;
}

void Rect::toSDLRect(SDL_Rect &rect) const
{
  size.toSDLRect(rect);
  origin.toSDLRect(rect);
}

Point Point::operator*(int_fast32_t v) const
{
  Point newPoint = *this;

  newPoint.x *= v;
  newPoint.y *= v;

  return newPoint;
}

Size Size::operator*(float v) const
{
  Size newSize = *this;

  newSize.width = static_cast<uint_fast32_t>(newSize.width * v);
  newSize.height = static_cast<uint_fast32_t>(newSize.height * v);

  return newSize;
}