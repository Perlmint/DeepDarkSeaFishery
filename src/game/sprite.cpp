#include "sprite.h"

#include <SDL2/SDL.h>

#include "texture.h"
#include "texture_cache.h"
#include "render_command.h"
#include "renderer.h"

class SpriteRenderCommand : public RenderCommand
{
public:
  SpriteRenderCommand(std::weak_ptr<Texture> &&texture, const Rect &src, const Rect dst)
    : texture(texture)
    , srcRect(src)
    , dstRect(dst)
  {}

  void render(SDL_Renderer *renderer) override
  {
    SDL_Rect srcSdlRect, dstSdlRect;
    srcRect.toSDLRect(srcSdlRect);
    dstRect.toSDLRect(dstSdlRect);

    if (auto texturePtr = texture.lock())
    {
      SDL_RenderCopy(renderer, texturePtr->getTexture(), &srcSdlRect, &dstSdlRect);
    }
  }

private:
  std::weak_ptr<Texture> texture;
  Rect srcRect;
  Rect dstRect;
};

#ifdef _MSC_VER
Sprite *Sprite::Load(const uint32_t &id)
{
  Sprite *sprite = new Sprite();

  if (auto cache = TextureCache::Instance().lock())
  {
    sprite->texture = cache->loadFromID(id).lock();
    sprite->currentRect.size = sprite->texture->size();
  }

  return sprite;
}
#else
Sprite *Sprite::Load(const std::string &path)
{
  Sprite *sprite = new Sprite();

  if (auto cache = TextureCache::Instance().lock())
  {
    sprite->texture = cache->loadFromPath(path).lock();
    sprite->currentRect.size = sprite->texture->size();
  }

  return sprite;
}
#endif

Sprite::Sprite(const Sprite &org)
  : texture(org.texture)
{
}

Sprite::Sprite()
{
  
}

void Sprite::render(SDL_Renderer *renderer, const Point &pos)
{
  Rect dstRect = currentRect;
  dstRect.size *= scale;
  dstRect.origin = position - (dstRect.size / 2);
  SpriteRenderCommand(texture, currentRect, dstRect);
}

void Sprite::update(float dt)
{
  
}