#pragma once

#include <memory>
#include <vector>

#include "util.h"
#include "texture.h"
#include "render_command.h"

struct SDL_Renderer;

class SpriteRenderCommand : public RenderCommand
{
public:
  SpriteRenderCommand(int32_t zOrder, std::weak_ptr<Texture> &&texture, const Rect &src, const Rect dst);
  CommandType type() const override { return CommandType::SPRITE; }
  void render(SDL_Renderer *renderer) override;
  size_t key() const override { return texture.lock()->getHash(); }

private:
  std::weak_ptr<Texture> texture;
  Rect srcRect;
  Rect dstRect;
};