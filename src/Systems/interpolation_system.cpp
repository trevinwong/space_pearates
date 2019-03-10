#include "interpolation_system.hpp"

void InterpolationSystem::update(EntityManager & entityManager, float dt)
{
  vector<shared_ptr<Entity>> entities = entityManager.getEntities(entityManager.getComponentChecker(
    vector<int>{ComponentType::spline, ComponentType::transform, ComponentType::collision}));
  
  for (shared_ptr<Entity> e : entities) {
    shared_ptr<SplineComponent> spline = e->getComponent<SplineComponent>();
    shared_ptr<TransformComponent> transform = e->getComponent<TransformComponent>();
    shared_ptr<CollisionComponent> collision = e->getComponent<CollisionComponent>();

    vec2 new_pos = catmull_rom_spline(spline->controlPoints, spline->getTime());
    transform->position = new_pos;
    collision->position = new_pos;
    spline->incrementTime(dt);
    if (spline->isExpired) {
      entityManager.removeEntity(e);
    }
  }
}

//https://stackoverflow.com/questions/37230747/how-can-i-generate-a-spline-curve-using-glm-gtx-splinecatmullrom
//Given a vector cp of n control points, compute the value of the Catmull-Rom spline at parameter t (where t goes from 0 to n-1):
vec2 InterpolationSystem::catmull_rom_spline(const vector<vec2>& cp, float t)
{
  // indices of the relevant control points
  int i0 = (int)glm::clamp(t - 1, 0.0f, (float)cp.size() - 1);
  int i1 = (int)glm::clamp(t, 0.0f, (float)cp.size() - 1);
  int i2 = (int)glm::clamp(t + 1, 0.0f, (float)cp.size() - 1);
  int i3 = (int)glm::clamp(t + 2, 0.0f, (float)cp.size() - 1);

  // parameter on the local curve interval
  float local_t = glm::fract(t);

  return glm::catmullRom(cp[i0], cp[i1], cp[i2], cp[i3], local_t);
}
