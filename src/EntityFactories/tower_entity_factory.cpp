#include "tower_entity_factory.hpp"

Entity TowerEntityFactory::createFireTower(vec2 towerCenterBottomPosition, vec2 _size)
{
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram, 100);

  TransformComponent *transform = new TransformComponent(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  ColorComponent *color = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("fire_tower.png"), true);
  SpriteComponent *sprite = new SpriteComponent(towerProgram, towerTexture);

  Program *towerRangeProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerRangeTexture = new Texture(texture_path("fire_tower_range.png"), true);
  TowerRangeSpriteComponent *towerRangeSprite = new TowerRangeSpriteComponent(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 120.0f;
  int maxLevel = 3;
  float fireRate = 6.0f; // increasing this slows the fire rate...
  int projectileAttackPower = 10;
  FireTowerAttackComponent *fireTowerAttack = new FireTowerAttackComponent(
    relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  TowerMetaComponent *towerMeta = new TowerMetaComponent(buildCost, sellGet, upgradeCost);

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
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram, 100);

  TransformComponent *transform = new TransformComponent(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  ColorComponent *color = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("water_tower.png"), true);
  SpriteComponent *sprite = new SpriteComponent(towerProgram, towerTexture);

  Program *towerRangeProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerRangeTexture = new Texture(texture_path("water_tower_range.png"), true);
  TowerRangeSpriteComponent *towerRangeSprite = new TowerRangeSpriteComponent(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, 0.0);
  float attackRange = 250.0f;
  int maxLevel = 3;
  int projectileNumberPerShoot = 4;
  float slowDownFactor = 0.65f;
  WaterTowerAttackComponent *waterTowerAttack = new WaterTowerAttackComponent(
    relativeFirePosition, attackRange, maxLevel, slowDownFactor);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  TowerMetaComponent *towerMeta = new TowerMetaComponent(buildCost, sellGet, upgradeCost);

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
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram, 100);

  TransformComponent *transform = new TransformComponent(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  ColorComponent *color = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("light_tower.png"), true);
  SpriteComponent *sprite = new SpriteComponent(towerProgram, towerTexture);

  Program *towerRangeProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerRangeTexture = new Texture(texture_path("light_tower_range.png"), true);
  TowerRangeSpriteComponent *towerRangeSprite = new TowerRangeSpriteComponent(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 180.0f;
  int maxLevel = 2;
  float fireRate = 8.0f;
  int projectileAttackPower = 10;
  int projectileNumberPerShoot = 4;
  LightTowerAttackComponent *lightTowerAttack = new LightTowerAttackComponent(
    relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower, projectileNumberPerShoot);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  TowerMetaComponent *towerMeta = new TowerMetaComponent(buildCost, sellGet, upgradeCost);

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
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram, 100);

  TransformComponent *transform = new TransformComponent(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  ColorComponent *color = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("star_tower.png"), true);
  SpriteComponent *sprite = new SpriteComponent(towerProgram, towerTexture);

  Program *towerRangeProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerRangeTexture = new Texture(texture_path("star_tower_range.png"), true);
  TowerRangeSpriteComponent *towerRangeSprite = new TowerRangeSpriteComponent(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 180.0f;
  int maxLevel = 1;
  float fireRate = 4.0f;
  int projectileAttackPower = 10;
  vec2 projectileSize = vec2(10, 10);
  StarTowerAttackComponent *starTowerAttack = new StarTowerAttackComponent(
    relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower, projectileSize);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  TowerMetaComponent *towerMeta = new TowerMetaComponent(buildCost, sellGet, upgradeCost);

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
  Program *billboardProgram = new Program(shader_path("billboard.vert"), shader_path("billboard.frag"));
  HealthComponent *health = new HealthComponent(billboardProgram, 100);

  TransformComponent *transform = new TransformComponent(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  ColorComponent *color = new ColorComponent(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  Program *towerProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerTexture = new Texture(texture_path("boomerang_tower.png"), true);
  SpriteComponent *sprite = new SpriteComponent(towerProgram, towerTexture);

  Program *towerRangeProgram = new Program(shader_path("sprite.vert"), shader_path("sprite.frag"));
  Texture *towerRangeTexture = new Texture(texture_path("light_tower_range.png"), true);//TODO
  TowerRangeSpriteComponent *towerRangeSprite = new TowerRangeSpriteComponent(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  float attackRange = 180.0f;
  int maxLevel = 1;
  float fireRate = 14.0f; //TODO maybe change this for level up too - tower specific power ups
  int projectileAttackPower = 1; //TODO smaller...
  BoomerangTowerAttackComponent *boomerangTowerAttack = new BoomerangTowerAttackComponent(
    relativeFirePosition, attackRange, maxLevel, fireRate, projectileAttackPower);

  int buildCost = 1;
  int sellGet = 1;
  int upgradeCost = 2;
  TowerMetaComponent *towerMeta = new TowerMetaComponent(buildCost, sellGet, upgradeCost);

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