#include "renderer.h"
#include "render_command.h"

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
  for (auto &commands : instance->commands)
  {
    switch (std::get<1>(commands.first))
    {
    case CommandType::SPRITE:
      commands.second->render(instance->renderer);
      break;
    }
  }
  instance->commands.clear();
}

void Renderer::queueCommand(std::shared_ptr<RenderCommand> &command)
{
  instance->commands.emplace(std::make_tuple(command->z(), command->type(), command->key()), command);
}