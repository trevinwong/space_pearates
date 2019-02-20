#ifndef OFFSCREEN_GARBAGE_SYSTEM_H
#define OFFSCREEN_GARBAGE_SYSTEM_H

#include <vector>
#include "utility.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Components/projectile_component.hpp"
#include "../Components/transform_component.hpp"

/*
  Any entity which has one of the component in targetEntitiesHasOneOfComponents will be checked if offscreen
  The enetity will be destroyed if offscreen

  e.g.
  if targetEntitiesHasOneOfComponents = { ComponentType::A, ComponentType::E, ComponentType::F }
  then all entities which contain A, OR contain E, OR contain F will be checked
*/
class OffscreenGarbageSystem {
  public:
    OffscreenGarbageSystem();
    ~OffscreenGarbageSystem();
    void destroyOffScreenEntities(EntityManager & entityManager);
  private:
    vector<int> targetEntitiesCharacterizedComponents = { ComponentType::projectile };
};

#endif // !OFFSCREEN_GARBAGE_SYSTEM_H
