#include "collision_event.hpp"

CollisionEvent::CollisionEvent(Entity &e1, Entity &e2)
{
  cout << "COLLIDED" << endl;
}

CollisionEvent::~CollisionEvent()
{
}
