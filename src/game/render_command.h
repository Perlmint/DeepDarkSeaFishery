#pragma once

struct SDL_Renderer;

enum class CommandType : uint16_t {
  SPRITE
};

class RenderCommand
{
public:
  RenderCommand(uint32_t z) : _z(z) {}
  int32_t z() { return _z; }
  virtual size_t key() const = 0;
  virtual CommandType type() const = 0;
  virtual void render(SDL_Renderer *renderer) = 0;
protected:
  uint32_t _z;
};
