#pragma once

struct SDL_Renderer;

class RenderCommand;

class Renderer
{
public:
  static SDL_Renderer *get();
  static void init(SDL_Renderer *);
  static void destroy();
  static void clear();
  static void render();
  static void queueCommand(const RenderCommand &command);

private:
  static Renderer *Instance();
  static Renderer *instance;
  SDL_Renderer *renderer;
};
