#include "collision_system.hpp"

void CollisionSystem::checkCollisions(EventSystem &eventSystem, vector<Entity> &entities)
{
  std::vector<Entity> collisionEntities;

  for (Entity &e : entities) {
    CollisionComponent *collision = e.getComponent<CollisionComponent>();
    if (collision != nullptr) {
      collisionEntities.push_back(e);
    }
  }

  for (Entity &e1 : collisionEntities) {
    for (Entity &e2 : collisionEntities) {
      if (e1 == e2) continue;

      if (isCollision(e1, e2)) {
        cout << "COLLIDED" << endl;
        eventSystem.propagateEvent(new CollisionEvent());
      }
    }
  }
}

void CollisionSystem::processEvent(Event *event)
{

}

bool CollisionSystem::isCollision(Entity &one, Entity &two) // AABB - AABB collision
{
  TransformComponent *one_p = one.getComponent<TransformComponent>();
  MovementComponent *one_v = one.getComponent<MovementComponent>();
  TransformComponent *two_p = two.getComponent<TransformComponent>();
  MovementComponent *two_v = two.getComponent<MovementComponent>();

  // Collision x-axis?
  bool collisionX = one_p->position.x + one_p->size.x > two_p->position.x &&
    two_p->position.x + two_p->size.x > one_p->position.x;

  //// Collision y-axis?
  bool collisionY = one_p->position.y + one_p->size.y > two_p->position.y &&
    two_p->position.y + two_p->size.y > one_p->position.y;

  //// Collision only if on both axes
  return collisionX && collisionY;
}

/*float dx = m_position.x - turtle.get_position().x;
    float dy = m_position.y - turtle.get_position().y;
    float d_sq = dx * dx + dy * dy;
    float other_r = std::max(collision->size.x, collision->size.y);
    float my_r = std::max(m_scale.x, m_scale.y);
    float r = std::max(other_r, my_r);
    r *= 0.6f;
    if (d_sq < r * r)
      return true;
    return false;*/
