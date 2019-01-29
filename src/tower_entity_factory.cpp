#include "tower_entity_factory.hpp"

Entity TowerEntityFactory::createTower(glm::vec2 towerCenterBottomPosition, glm::vec2 _size)
{
  
  Entity towerEntity;
  // calculate left top x,y coord
  float x = towerCenterBottomPosition.x - _size.x / 2.0;
  float y = towerCenterBottomPosition.y - _size.y;
  glm::vec2 position = {x, y};

  Program *program = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerSampletexture = new Texture();

  SpriteComponent *spriteComponent = new SpriteComponent(program, towerSampletexture);
  TransformComponent *transformComponent = new TransformComponent(position, _size, 0.0f);
  ColorComponent *colorComponent = new ColorComponent(glm::vec4(1.0f, 0.325f, 0.051f, 1.0f)); // diff tower can have diff color
  towerEntity.setComponent<SpriteComponent>(spriteComponent);
  towerEntity.setComponent<TransformComponent>(transformComponent);
  towerEntity.setComponent<ColorComponent>(colorComponent);

  return towerEntity;
}