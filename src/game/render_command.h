#pragma once

class RenderCommand
{
public:
  virtual void render(SDL_Renderer *renderer) = 0;
};
