#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Utility/timer.hpp"
#include "../EntityFactories/particle_factory.hpp"
#include "../Components/sprite_component.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/color_component.hpp"
#include "../Components/particle_component.hpp"
#include "../Components/health_component.hpp"
#include "../Components/home_component.hpp"

class ParticleSystem {
public:
  void initParticleSystem(EntityManager & manager);
  static void emitParticleCluster(EntityManager & manager, vec2 clusterOrigin); // Create a particle cluster at posn clusterOrigin
  static void updateParticles(EntityManager & manager, float dt);
  static vector<shared_ptr<Entity>> particleClusters;
  static int findUnusedParticle();
  static void emitSmoke(EntityManager & manager, glm::vec2 clusterOrigin);
  //TODO: destroy()
};
#endif
