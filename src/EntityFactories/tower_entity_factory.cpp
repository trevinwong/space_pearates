#include "tower_entity_factory.hpp"

Entity TowerEntityFactory::createFireTower(vec2 towerCenterBottomPosition, vec2 _size)
{
  shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, 100);

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("fire_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("fire_tower_range.png"), true);
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 120.0f;
  int maxLevel = 3;
  float fireRate = 2.0f; // increasing this slows the fire rate...
  int projectileAttackPower = 20;
  shared_ptr<FireTowerAttackComponent> fireTowerAttack = make_shared<FireTowerAttackComponent>(
    relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(buildCost, sellGet, upgradeCost);

  Entity towerEntity;
  towerEntity.setComponent<SpriteComponent>(sprite);
  towerEntity.setComponent<TransformComponent>(transform);
  towerEntity.setComponent<ColorComponent>(color);
  towerEntity.setComponent<TowerMetaComponent>(towerMeta);
  towerEntity.setComponent<HealthComponent>(health);
  towerEntity.setComponent<FireTowerAttackComponent>(fireTowerAttack);
  towerEntity.setComponent<TowerRangeSpriteComponent>(towerRangeSprite);
  return towerEntity;
}

Entity TowerEntityFactory::createWaterTower(vec2 towerCenterBottomPosition, vec2 _size)
{
  shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, 100);

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("water_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("water_tower_range.png"), true);
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, 0.0);
  float attackRange = 250.0f;
  int maxLevel = 3;
  float slowDownFactor = 0.65f;
  shared_ptr<WaterTowerAttackComponent> waterTowerAttack = make_shared<WaterTowerAttackComponent>(
    relativeFirePosition, attackRange, maxLevel, slowDownFactor);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(buildCost, sellGet, upgradeCost);

  Entity towerEntity;
  towerEntity.setComponent<SpriteComponent>(sprite);
  towerEntity.setComponent<TransformComponent>(transform);
  towerEntity.setComponent<ColorComponent>(color);
  towerEntity.setComponent<HealthComponent>(health);
  towerEntity.setComponent<TowerMetaComponent>(towerMeta);
  towerEntity.setComponent<WaterTowerAttackComponent>(waterTowerAttack);
  towerEntity.setComponent<TowerRangeSpriteComponent>(towerRangeSprite);
  return towerEntity;
}

Entity TowerEntityFactory::createLightTower(vec2 towerCenterBottomPosition, vec2 _size)
{
  shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, 100);

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("light_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("light_tower_range.png"), true);
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 180.0f;
  int maxLevel = 2;
  float fireRate = 2.5f;
  int projectileAttackPower = 20;
  int projectileNumberPerShoot = 4;
  shared_ptr<LightTowerAttackComponent> lightTowerAttack = make_shared<LightTowerAttackComponent>(
    relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower, projectileNumberPerShoot);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(buildCost, sellGet, upgradeCost);

  Entity towerEntity;
  towerEntity.setComponent<SpriteComponent>(sprite);
  towerEntity.setComponent<TransformComponent>(transform);
  towerEntity.setComponent<ColorComponent>(color);
  towerEntity.setComponent<HealthComponent>(health);
  towerEntity.setComponent<TowerMetaComponent>(towerMeta);
  towerEntity.setComponent<LightTowerAttackComponent>(lightTowerAttack);
  towerEntity.setComponent<TowerRangeSpriteComponent>(towerRangeSprite);
  return towerEntity;
}

Entity TowerEntityFactory::createStarTower(vec2 towerCenterBottomPosition, vec2 _size)
{
  shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, 100);

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("star_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("star_tower_range.png"), true);
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 180.0f;
  int maxLevel = 1;
  float fireRate = 2.5f;
  int projectileAttackPower = 40;
  vec2 projectileSize = vec2(10, 10);
  shared_ptr<StarTowerAttackComponent> starTowerAttack = make_shared<StarTowerAttackComponent>(
    relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower, projectileSize);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(buildCost, sellGet, upgradeCost);

  Entity towerEntity;
  towerEntity.setComponent<SpriteComponent>(sprite);
  towerEntity.setComponent<TransformComponent>(transform);
  towerEntity.setComponent<ColorComponent>(color);
  towerEntity.setComponent<HealthComponent>(health);
  towerEntity.setComponent<TowerMetaComponent>(towerMeta);
  towerEntity.setComponent<StarTowerAttackComponent>(starTowerAttack);
  towerEntity.setComponent<TowerRangeSpriteComponent>(towerRangeSprite);
  return towerEntity;
}

Entity TowerEntityFactory::createBoomerangTower(vec2 towerCenterBottomPosition, vec2 _size)
{
  shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, 100);

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("boomerang_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("light_tower_range.png"), true);//TODO
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 180.0f;
  int maxLevel = 1;
  float fireRate = 3.0f; //TODO maybe change this for level up too - tower specific power ups
  int projectileAttackPower = 10; //TODO Adjust this (currently applies damage per frame)
  shared_ptr<BoomerangTowerAttackComponent> boomerangTowerAttack = make_shared<BoomerangTowerAttackComponent>(
    relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(buildCost, sellGet, upgradeCost);

  Entity towerEntity;
  towerEntity.setComponent<SpriteComponent>(sprite);
  towerEntity.setComponent<TransformComponent>(transform);
  towerEntity.setComponent<ColorComponent>(color);
  towerEntity.setComponent<HealthComponent>(health);
  towerEntity.setComponent<TowerMetaComponent>(towerMeta);
  towerEntity.setComponent<BoomerangTowerAttackComponent>(boomerangTowerAttack);
  towerEntity.setComponent<TowerRangeSpriteComponent>(towerRangeSprite);
  return towerEntity;
}

vec2 TowerEntityFactory::getTopLeftPosition(vec2 centerBottom, vec2 size) {
  float x = centerBottom.x - size.x / 2.0;
  float y = centerBottom.y - size.y;
  return { x, y };
}
