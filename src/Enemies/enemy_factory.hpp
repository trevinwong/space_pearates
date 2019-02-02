#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include "entity.hpp"
#include "program.hpp"
#include "sprite_component.hpp"
#include "transform_component.hpp"
#include "color_component.hpp"

class EnemyFactory
{
public:
  EnemyFactory();
  ~EnemyFactory();
  Entity build(glm::vec2 position, glm::vec2 scale);
private:

};

#endif