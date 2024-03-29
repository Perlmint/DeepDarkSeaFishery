#pragma once
#include <memory>
#include <cstdint>
#include <string>
#include "util.h"

struct SDL_Renderer;
class Texture;
class Animation;

class Sprite
{
public:
#ifdef _MSC_VER
  // for windows resources
  static Sprite *Load(const uint32_t &id);
#else
  // for other platform resources
  static Sprite *Load(const std::string &path);
#endif

  Sprite(const Sprite &org);

  void render(SDL_Renderer *renderer, const Point &pos);
  void update(float dt);

  void setScale(float factor) { scale = factor; }
  float getScale() { return scale; }
  Point::Setter Position() { return Point::Setter(position); }

private:
  Sprite();
  std::shared_ptr<Texture> texture;
  Rect currentRect;
  Point position;
  float scale = 1.f;
};