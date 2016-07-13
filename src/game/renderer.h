#pragma once

#include <memory>
#include <map>

struct SDL_Renderer;

class RenderCommand;

enum class CommandType : uint16_t;

class Renderer
{
public:
  static SDL_Renderer *get();
  static void init(SDL_Renderer *);
  static void destroy();
  static void clear();
  static void render();
  static void queueCommand(std::shared_ptr<RenderCommand> &command);

private:
  static Renderer *Instance();
  static Renderer *instance;
  SDL_Renderer *renderer;
  std::multimap<std::tuple<int32_t, CommandType, size_t>, std::shared_ptr<RenderCommand>> commands;
};
