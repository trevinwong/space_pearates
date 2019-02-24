#ifndef BACKGROUND_SYSTEM_H
#define BACKGROUND_SYSTEM_H

#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "entity_manager.hpp"
#include "../Components/background_component.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/color_component.hpp"

class BackgroundSystem
{
public:
  void update(EntityManager &entityManager);
  void render(EntityManager &entityManager, glm::mat4 projection);
};

#endif