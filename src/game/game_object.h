#pragma once
#include<memory>

class GameObject : std::enable_shared_from_this<GameObject>
{
public:
  GameObject();
};
