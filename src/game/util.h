#pragma once
#include <cstdint>

struct SDL_Rect;

class Size;
class Rect;

class Vec2
{
public:
  Vec2(int_fast32_t v1, int_fast32_t v2) : v1(v1), v2(v2) {}

  int_fast32_t v1, v2;
};

class Point
{
public:
  Point()
  : x(0), y(0)
  {}

  Point(int_fast32_t x, int_fast32_t y)
    : x(x), y(y)
  {}

  Point(const Point &) = default;

  void toSDLRect(SDL_Rect &) const;

  Point operator*(int_fast32_t) const;
  Point operator-(const Vec2 &v) const { return Point(x - v.v1, y - v.v2); }
  Point operator+(const Vec2 &v) const { return Point(x + v.v1, y + v.v2); }
  bool operator==(const Point &p) const { return p.x == x && p.y == y; }

  int_fast32_t x;
  int_fast32_t y;
  
  operator Vec2() const { return Vec2(x, y); }

  class Setter
  {
  public:
    Setter(Point &p)
      : point(p) {}

    Setter &operator=(const Point &p) { point = p; return *this; }
    Setter &x(int_fast32_t x) { point.x = x; return *this; }
    Setter &y(int_fast32_t y) { point.y = y; return *this; }
  private:
    Point &point;
  };
};

class Size
{
public:
  Size()
  : width(0), height(0)
  {}

  Size(int_fast32_t w, int_fast32_t h)
    : width(w), height(h)
  {}

  Size(const Size &) = default;

  void toSDLRect(SDL_Rect &) const;

  Size operator*(float) const;
  Size &operator*=(float &v) { *this = *this * v; return *this; }
  Size operator/(float v) const { return *this * (1 / v);}
  Size &operator/=(float &v) { *this = *this / v; return *this; }
  bool operator==(const Size &s) const { return s.width == width && s.height == height; }

  uint_fast32_t width;
  uint_fast32_t height;

  operator Vec2() const { return Vec2(width, height); }
};

class Rect
{
public:
  Rect() {};

  Rect(const Point &origin, const Size &size)
    : origin(origin), size(size)
  {}

  Rect(const Rect &) = default;

  void toSDLRect(SDL_Rect &) const;
  bool operator==(const Rect &r) const { return r.origin == origin && r.size == size; }

  Point origin;
  Size size;
};
