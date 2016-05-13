#include <string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "platform.h"
#include "game/sprite.h"
#include "game/texture.h"
#include "game/renderer.h"

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

float GameHeight = 200.0f;

void main_loop()
{
  bool running = true;
  SDL_Event events;
  Uint32 start;
  
  Sprite *sprite = Sprite::LoadFromPath("grass.png");
  sprite->setScale(2.0f);

  while(running)
  {
    start = SDL_GetTicks();
    while(SDL_PollEvent(&events))
    {
      switch(events.type)
      {
        case SDL_KEYDOWN:
          break;
        case SDL_KEYUP:
          break;
        case SDL_MOUSEBUTTONDOWN:
          break;
        case SDL_MOUSEBUTTONUP:
          break;
        case SDL_MOUSEMOTION:
          break;
        case SDL_QUIT:
          running = false;
          break;
      }
    }

    Renderer::clear();
    SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
    sprite->render(Renderer::get(), Point(0, 0));
    SDL_RenderPresent(sdlRenderer);

    //frame regulation
    if(1000/30 > SDL_GetTicks() - start)
    {
      SDL_Delay(1000/30 - (SDL_GetTicks() - start));
    }
  }
}

int main(int /* argc */, char */* argv */[])
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(300, 400, SDL_WINDOW_BORDERLESS, &sdlWindow, &sdlRenderer);
  Renderer::init(sdlRenderer);

  initWindow(sdlWindow);
  initRenderer(sdlRenderer);

  main_loop();

  Renderer::destroy();
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(sdlWindow);
  SDL_Quit();
  return 0;
}
