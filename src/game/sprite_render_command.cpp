#include "sprite_render_command.h"
#include "SDL.h"

SpriteRenderCommand::SpriteRenderCommand(int32_t zOrder, std::weak_ptr<Texture> &&texture, const Rect &src, const Rect dst)
  : RenderCommand(zOrder)
  , texture(texture)
  , srcRect(src)
  , dstRect(dst)
{}

void SpriteRenderCommand::render(SDL_Renderer *renderer)
{
  SDL_Rect srcSdlRect, dstSdlRect;
  srcRect.toSDLRect(srcSdlRect);
  dstRect.toSDLRect(dstSdlRect);

  if (auto texturePtr = texture.lock())
  {
    SDL_RenderCopy(renderer, texturePtr->getTexture(), &srcSdlRect, &dstSdlRect);
  }
}