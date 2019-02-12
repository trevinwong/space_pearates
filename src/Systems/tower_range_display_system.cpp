#include "tower_range_display_system.hpp"

TowerRangeDisplaySystem::TowerRangeDisplaySystem()
{
}

TowerRangeDisplaySystem::~TowerRangeDisplaySystem()
{
}

void TowerRangeDisplaySystem::drawRanges(EntityManager & entityManager, glm::mat4 projection)
{
  vector<shared_ptr<Entity>> player_entities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::player}));
  vector<shared_ptr<Entity>> map_entities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::map}));
  vector<shared_ptr<Entity>> tower_entities =
    entityManager.getEntitiesHasOneOf(entityManager.getComponentChecker(vector<int> {ComponentType::fire_tower_range_sprite, ComponentType::light_tower_range_sprite}));

  // cannot find map or player
  // or there is no tower in the world now
  if (map_entities.size() == 0 || player_entities.size() == 0 || tower_entities.size() == 0) return;

  auto player_entity = player_entities[0];
  auto map_entity = map_entities[0];

  TransformComponent *playerTransformComponent = player_entity->getComponent<TransformComponent>();
  glm::vec2 playerPosition = playerTransformComponent->position;
  glm::vec2 playerCenterPosition = playerPosition + playerTransformComponent->size * 0.5f;

  MapComponent *mapComponent = map_entity->getComponent<MapComponent>();
  float mapTileWidth = mapComponent->width_tile;
  float mapTileHeight = mapComponent->height_tile;


  for (shared_ptr<Entity> e : tower_entities)
  {

    TransformComponent *transformComponent = e->getComponent<TransformComponent>();
    if (transformComponent == nullptr) continue;

    // a tower may contain multi attack component
    FireTowerAttackComponent *fireTowerAttackComponent = e->getComponent<FireTowerAttackComponent>();
    LightTowerAttackComponent *lightTowerAttackComponent = e->getComponent<LightTowerAttackComponent>();
    
    vector<TowerAttackComponent*> towerAttackComponents;
    if (fireTowerAttackComponent != nullptr)  towerAttackComponents.push_back(fireTowerAttackComponent);
    if (lightTowerAttackComponent != nullptr)  towerAttackComponents.push_back(lightTowerAttackComponent);

    for (TowerAttackComponent* towerAttackComponent : towerAttackComponents) {
      // calculate the positon of the range circle
      glm::vec2 towerLeftTopPosition = transformComponent->position;
      glm::vec2 towerSize = transformComponent->size;
      glm::vec2 towerCenterPosition = towerLeftTopPosition + towerSize * 0.5f;

      // check if player and a tower in the same tile
      // display range circle if they are in the same tile
      if (((int)(towerCenterPosition.x / mapTileWidth) == (int)(playerCenterPosition.x / mapTileWidth)) &&
        ((int)(towerCenterPosition.y / mapTileHeight) == (int)(playerCenterPosition.y / mapTileHeight))) {

        // towerRadius -> drawRangesHelper function
        float towerRadius = towerAttackComponent->getAttackRange();

        // shootRangeCircleCenterPosition -> drawRangesHelper function
        glm::vec2 relativeFirePosition = towerAttackComponent->getRelativeFirePosition();
        glm::vec2 shootRangeCircleCenterPosition(towerCenterPosition + towerSize * relativeFirePosition);

        // fireTowerRangeSpriteComponent -> drawRangesHelper function
        FireTowerRangeSpriteComponent *fireTowerRangeSpriteComponent = e->getComponent<FireTowerRangeSpriteComponent>();
        // draw range
        drawRangesHelper(fireTowerRangeSpriteComponent, shootRangeCircleCenterPosition, towerRadius, projection);

        // lightTowerRangeSpriteComponent -> drawRangesHelper function
        LightTowerRangeSpriteComponent *lightTowerRangeSpriteComponent = e->getComponent<LightTowerRangeSpriteComponent>();
        // draw range
        drawRangesHelper(lightTowerRangeSpriteComponent, shootRangeCircleCenterPosition, towerRadius, projection);
      }
    }
    
  }
}

void TowerRangeDisplaySystem::drawRangesHelper(SpriteComponent *towerRangeSpriteComponent, glm::vec2 shootRangeCircleCenterPosition, float towerRadius, glm::mat4 projection)
{
  if (towerRangeSpriteComponent == nullptr) return;

  // Use the program attached with the spriteComponent.
  towerRangeSpriteComponent->program->use();

  // Make sure to initialize glm::mat4 to the identity matrix, otherwise matrix transformations will not work.
  glm::mat4 model = glm::mat4(1.0);

  // We want to scale, rotate, then translate.
  // But since matrix operations happen from right to left, we want to code these operations in reverse order.
  model = glm::translate(model, glm::vec3(shootRangeCircleCenterPosition - towerRadius, 0.0f));

  // Rotation
  // model = glm::translate(model, glm::vec3(0.5f * towerSize, 0.0f));
  // model = glm::rotate(model, transformComponent->rotate, glm::vec3(0.0f, 0.0f, 1.0f));
  // model = glm::translate(model, glm::vec3(-0.5f * transformComponent->size.x, -0.5f * transformComponent->size.y, 0.0f));

  model = glm::scale(model, glm::vec3(glm::vec2(towerRadius*2.0, towerRadius*2.0), 1.0f));

  towerRangeSpriteComponent->program->setMat4("model", model);
  towerRangeSpriteComponent->program->setMat4("projection", projection);
  towerRangeSpriteComponent->program->setVec4("spriteColor", glm::vec4(1.0, 1.0, 1.0, 1.0));

  // Activate texture unit 0.
  // We can have multiple texture units to use as uniforms in our shader, but we only need 1.
  glActiveTexture(GL_TEXTURE0);
  // Bind our texture so we can render it over the quad of our sprite.
  towerRangeSpriteComponent->texture->bind();

  // Bind our VAO which contains the quad VBO we defined and our definitions for its coordinates and texture coordinates.
  glBindVertexArray(towerRangeSpriteComponent->quadVAO);
  // Draw our sprite.
  glDrawArrays(GL_TRIANGLES, 0, 6);
  // Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
  glBindVertexArray(0);
}
