#include "renderer.h"

#include <memory>

#include <SDL2/SDL.h>

Renderer *Renderer::instance = nullptr;

SDL_Renderer *Renderer::get()
{
  return Instance()->renderer;
}

void Renderer::init(SDL_Renderer *renderer)
{
  Instance()->renderer = renderer;
}

void Renderer::destroy()
{
  if (instance != nullptr)
  {
    delete instance;
  }
}

Renderer *Renderer::Instance()
{
  if (instance == nullptr) {
    instance = new Renderer();
  }

  return instance;
}

void Renderer::clear()
{
  auto renderer = get();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
}

void Renderer::render()
{
  
}

void Renderer::queueCommand(const RenderCommand &command)
{
  
}