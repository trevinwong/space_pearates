#ifndef HOME_SYSTEM_H
#define HOME_SYSTEM_H

#include "Utility/utility.hpp"
#include "Utility/audio_loader.hpp"
#include "entity_manager.hpp"
#include "entity.hpp"
#include "Components/home_component.hpp"
#include "Components/health_component.hpp"
#include "Components/sprite_component.hpp"

class HomeSystem
{
public:
  void handleCriticalState(shared_ptr<Entity> home);
  void resetCriticalState(shared_ptr<Entity> home);
  void checkState(EntityManager &entityManager);
  void reset(EntityManager &entityManager);
  bool alert_played = false;
};

#endif
