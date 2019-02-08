#include "collision_event.hpp"

CollisionEvent::CollisionEvent(shared_ptr<Entity> e1, shared_ptr<Entity> e2)
{
  cout << "COLLIDED" << endl;
}

CollisionEvent::~CollisionEvent()
{
}
