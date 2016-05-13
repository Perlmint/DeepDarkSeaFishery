#include "world.h"

class World::World_internal
{
public:
  World_internal()
  {
    
  }

  World_internal(uint32_t width, uint32_t height)
  {
    
  }

private:
};

World::World()
  : internal(new World_internal())
{
}

World::World(uint32_t width, uint32_t height)
  : internal(new World_internal(width, height))
{
}