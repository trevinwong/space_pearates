#include "tower_entity_factory.hpp"

Entity TowerEntityFactory::createFireTower(vec2 towerCenterBottomPosition, vec2 _size)
{
  shared_ptr<Program> billboardProgram = make_shared<Program>(shader_path("billboard.vert"), shader_path("billboard.frag"));
  shared_ptr<HealthComponent> health = make_shared<HealthComponent>(billboardProgram, 100);

  shared_ptr<TransformComponent> transform = make_shared<TransformComponent>(getTopLeftPosition(towerCenterBottomPosition, _size), _size, 0.0f);
  shared_ptr<ColorComponent> color = make_shared<ColorComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); // diff tower can have diff color

  shared_ptr<Program> towerProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("towers/fire_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("fire_tower_range.png"), true);
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  shared_ptr<FireTowerData> data = std::dynamic_pointer_cast<FireTowerData>(TowerDataLoader::allTowerData[BUILD_FIRE_TOWER]);

  shared_ptr<FireTowerAttackComponent> fireTowerAttack = make_shared<FireTowerAttackComponent>(
    data->relativeFirePosition, data->attackPerLvl, data->rangePerLvl, data->fireRatePerLvl);

  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(data->buildCost, data->upgradeCostsPerLvl, data->maxLvl);

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
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("towers/water_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("water_tower_range.png"), true);
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  shared_ptr<WaterTowerData> data = std::dynamic_pointer_cast<WaterTowerData>(TowerDataLoader::allTowerData[BUILD_WATER_TOWER]);

  shared_ptr<WaterTowerAttackComponent> waterTowerAttack = make_shared<WaterTowerAttackComponent>(
    data->relativeFirePosition, data->rangePerLvl, data->slowPerLvl);

  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(data->buildCost, data->upgradeCostsPerLvl, data->maxLvl);

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
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("towers/light_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("light_tower_range.png"), true);
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  shared_ptr<LightTowerData> data = std::dynamic_pointer_cast<LightTowerData>(TowerDataLoader::allTowerData[BUILD_LIGHT_TOWER]);

  shared_ptr<LightTowerAttackComponent> lightTowerAttack = make_shared<LightTowerAttackComponent>(
    data->relativeFirePosition, data->attackPerLvl, data->rangePerLvl, data->fireRatePerLvl, data->numProjectilesPerLvl);

  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(data->buildCost, data->upgradeCostsPerLvl, data->maxLvl);

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
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("towers/star_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("star_tower_range.png"), true);
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  shared_ptr<StarTowerData> data = std::dynamic_pointer_cast<StarTowerData>(TowerDataLoader::allTowerData[BUILD_STAR_TOWER]);

  shared_ptr<StarTowerAttackComponent> starTowerAttack = make_shared<StarTowerAttackComponent>(
    data->relativeFirePosition, data->attackPerLvl, data->rangePerLvl, data->fireRatePerLvl, data->sizePerLvl);

  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(data->buildCost, data->upgradeCostsPerLvl, data->maxLvl);

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
  shared_ptr<Texture> towerTexture = make_shared<Texture>(texture_path("towers/boomerang_tower.png"), true);
  shared_ptr<SpriteComponent> sprite = make_shared<SpriteComponent>(towerProgram, towerTexture);

  shared_ptr<Program> towerRangeProgram = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));
  shared_ptr<Texture> towerRangeTexture = make_shared<Texture>(texture_path("light_tower_range.png"), true);//TODO
  shared_ptr<TowerRangeSpriteComponent> towerRangeSprite = make_shared<TowerRangeSpriteComponent>(towerRangeProgram, towerRangeTexture);

  vec2 relativeFirePosition(0.0, -0.3);
  shared_ptr<BoomerangTowerData> data = std::dynamic_pointer_cast<BoomerangTowerData>(TowerDataLoader::allTowerData[BUILD_BOOMERANG_TOWER]);

  shared_ptr<BoomerangTowerAttackComponent> boomerangTowerAttack = make_shared<BoomerangTowerAttackComponent>(
    relativeFirePosition, data->attackPerLvl, data->rangePerLvl, data->fireRatePerLvl);

  shared_ptr<TowerMetaComponent> towerMeta = make_shared<TowerMetaComponent>(data->buildCost, data->upgradeCostsPerLvl, data->maxLvl);

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
