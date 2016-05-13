#pragma once
#include <memory>

class World : public std::enable_shared_from_this<World>
{
public:
  World();
  World(uint32_t width, uint32_t height);

private:
  class World_internal;
  std::unique_ptr<World_internal> internal;
};