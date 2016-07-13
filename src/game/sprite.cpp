#include "sprite.h"

#include <SDL2/SDL.h>

#include "texture.h"
#include "texture_cache.h"
#include "sprite_render_command.h"
#include "renderer.h"



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
  Renderer::queueCommand(std::dynamic_pointer_cast<RenderCommand, SpriteRenderCommand>(std::shared_ptr<SpriteRenderCommand>(new SpriteRenderCommand(0, texture, currentRect, dstRect))));
}

void Sprite::update(float dt)
{
  
}