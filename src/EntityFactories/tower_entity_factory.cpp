#include "tower_entity_factory.hpp"

Entity TowerEntityFactory::createFireTower(glm::vec2 towerCenterBottomPosition, glm::vec2 _size)
{
  
  Entity towerEntity;
  // calculate left top x,y coord
  float x = towerCenterBottomPosition.x - _size.x / 2.0;
  float y = towerCenterBottomPosition.y - _size.y;
  glm::vec2 position = {x, y};

  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram);

  TransformComponent *transformComponent = new TransformComponent(position, _size, 0.0f);
  ColorComponent *colorComponent = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  // SpriteComponent
  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("fire_tower.png"), true);
  SpriteComponent *spriteComponent = new SpriteComponent(towerProgram, towerTexture);

  // TowerRangeSpriteComponent
  Program *towerRangeProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerRangeTexture = new Texture(texture_path("fire_tower_range.png"), true);
  FireTowerRangeSpriteComponent *fireTowerRangeSpriteComponent = new FireTowerRangeSpriteComponent(towerRangeProgram, towerRangeTexture);

  // Fire Tower Attack Component
  glm::vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 120.0f;
  float fireRate = 2.0f;
  int projectileAttackPower = 10;
  int maxLevel = 3;
  FireTowerAttackComponent *fireTowerAttackComponent = 
    new FireTowerAttackComponent(relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower);

  // Tower Meta Component
  TowerMetaComponent *towerMetaComponent = new TowerMetaComponent();

  towerEntity.setComponent<SpriteComponent>(spriteComponent);
  towerEntity.setComponent<TransformComponent>(transformComponent);
  towerEntity.setComponent<ColorComponent>(colorComponent);
  towerEntity.setComponent<TowerMetaComponent>(towerMetaComponent);
  towerEntity.setComponent<HealthComponent>(health);
  towerEntity.setComponent<FireTowerAttackComponent>(fireTowerAttackComponent);
  towerEntity.setComponent<FireTowerRangeSpriteComponent>(fireTowerRangeSpriteComponent);

  return towerEntity;
}

Entity TowerEntityFactory::createLightTower(glm::vec2 towerCenterBottomPosition, glm::vec2 _size)
{

  Entity towerEntity;
  // calculate left top x,y coord
  float x = towerCenterBottomPosition.x - _size.x / 2.0;
  float y = towerCenterBottomPosition.y - _size.y;
  glm::vec2 position = { x, y };

  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram);

  TransformComponent *transformComponent = new TransformComponent(position, _size, 0.0f);
  ColorComponent *colorComponent = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  // SpriteComponent
  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("light_tower.png"), true);
  SpriteComponent *spriteComponent = new SpriteComponent(towerProgram, towerTexture);

  // TowerRangeSpriteComponent
  Program *towerRangeProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerRangeTexture = new Texture(texture_path("light_tower_range.png"), true);
  LightTowerRangeSpriteComponent *lightTowerRangeSpriteComponent = new LightTowerRangeSpriteComponent(towerRangeProgram, towerRangeTexture);


  // Fire Tower Attack Component
  glm::vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 180.0f;
  float fireRate = 4.0f;
  int projectileAttackPower = 10;
  int maxLevel = 3;
  int projectileNumberPerShoot = 4;
  LightTowerAttackComponent *lightTowerAttackComponent =
    new LightTowerAttackComponent(relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower, projectileNumberPerShoot);

  // Tower Meta Component
  TowerMetaComponent *towerMetaComponent = new TowerMetaComponent();

  towerEntity.setComponent<SpriteComponent>(spriteComponent);
  towerEntity.setComponent<TransformComponent>(transformComponent);
  towerEntity.setComponent<ColorComponent>(colorComponent);
  towerEntity.setComponent<HealthComponent>(health);
  towerEntity.setComponent<TowerMetaComponent>(towerMetaComponent);
  towerEntity.setComponent<LightTowerAttackComponent>(lightTowerAttackComponent);
  towerEntity.setComponent<LightTowerRangeSpriteComponent>(lightTowerRangeSpriteComponent);

  return towerEntity;
}