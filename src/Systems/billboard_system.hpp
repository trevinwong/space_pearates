#ifndef BILLBOARD_SYSTEM_H
#define BILLBOARD_SYSTEM_H

#include "Utility/utility.hpp"
#include "Utility/texture.hpp"
#include "Utility/program.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "Components/base_component.hpp"
#include "Components/transform_component.hpp"
#include "Components/health_component.hpp"
#include "Components/home_component.hpp"

class BillboardSystem
{
public:
  BillboardSystem();
  ~BillboardSystem();
  // Iterates through all entities. If they have a Health component, they are rendered.
  void drawBillboards(EntityManager &entityManager, glm::mat4 projection);
};

#endif