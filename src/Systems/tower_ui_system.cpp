#include "tower_ui_system.hpp"

void TowerUiSystem::interpInput(EntityManager& entityManager, GLboolean keys[])
{
  vector<shared_ptr<Entity>> towerBuildUiEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::build_tower_ui, ComponentType::tower_ui_button_meta, ComponentType::operate_tower_ui, ComponentType::build_tower_ui}));
  if (towerBuildUiEntities.size() == 0) return;

  TowerUiStateComponent *towerUiStateComponent = towerBuildUiEntities[0]->getComponent<TowerUiStateComponent>();
  if (towerUiStateComponent == nullptr) return;

  towerUiStateComponent->input(entityManager, keys);
}

void TowerUiSystem::update(EntityManager& entityManager, float dt) {
  vector<shared_ptr<Entity>> towerBuildUiEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::build_tower_ui, ComponentType::tower_ui_button_meta, ComponentType::operate_tower_ui, ComponentType::build_tower_ui}));

  // get state machine
  // because all buttons are shared one state component, get one and execute one, no need to use for loop
  TowerUiStateComponent* state = towerBuildUiEntities[0]->getComponent<TowerUiStateComponent>();
  state->update(entityManager, dt);
}

void TowerUiSystem::render(EntityManager& entityManager, glm::mat4 projection) {
  vector<shared_ptr<Entity>> playerEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::player}));
  vector<shared_ptr<Entity>> mapEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::map}));
  vector<shared_ptr<Entity>> towerBuildUiEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::build_tower_ui, ComponentType::tower_ui_button_meta, ComponentType::operate_tower_ui, ComponentType::build_tower_ui}));

  if (playerEntities.size() == 0 || mapEntities.size() == 0 || towerBuildUiEntities.size() == 0) return;

  TransformComponent *playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();
  MapComponent *mapComponent = mapEntities[0]->getComponent<MapComponent>();
  BuildTowerUiComponent *buildTowerUiComponent = towerBuildUiEntities[0]->getComponent<BuildTowerUiComponent>();
  OperateTowerUiComponent *operateTowerUiComponent = towerBuildUiEntities[0]->getComponent<OperateTowerUiComponent>();
  if (playerTransformComponent == nullptr || mapComponent == nullptr || buildTowerUiComponent == nullptr || operateTowerUiComponent == nullptr) return;

  glm::vec2 playerPosition = playerTransformComponent->position;
  glm::vec2 playerCenterPosition = playerPosition + playerTransformComponent->size * 0.5f;

  // if the player is not at a block which can be used to build a tower, then do not render ui
  if (!mapComponent->canBuildTowerAt(playerCenterPosition.x, playerCenterPosition.y)) return;

  // update button icon images
  for (shared_ptr<Entity> towerBuildUiEntity : towerBuildUiEntities) {
    TowerUiButtonComponent *towerUiButtonComponent = towerBuildUiEntity->getComponent<TowerUiButtonComponent>();
    if (towerUiButtonComponent == nullptr) continue;

    if (mapComponent->isTowerAt(playerCenterPosition.x, playerCenterPosition.y))
    {
      int index = operateTowerUiComponent->getCurrentSelectedTowerOperationListIndex();
      towerUiButtonComponent->texture = operateTowerUiComponent->getTowerOperationListUiIconsAt(index + towerUiButtonComponent->relativeIndex);
    }
    else
    {
      int index = buildTowerUiComponent->getCurrentSelectedTowerTypeListIndex();
      towerUiButtonComponent->texture = buildTowerUiComponent->getTowerTypeListUiIconsAt(index + towerUiButtonComponent->relativeIndex);
    }
  }

  renderTowerUiButtons(towerBuildUiEntities, projection);
}

void TowerUiSystem::renderTowerUiButtons(vector<shared_ptr<Entity>> towerBuildUiEntities, glm::mat4 projection) {
  vector<TowerUiButtonComponent*> towerUiButtonComponents;

  for (shared_ptr<Entity> towerBuildUiEntity : towerBuildUiEntities) {
    TowerUiButtonComponent *towerUiButtonComponent = towerBuildUiEntity->getComponent<TowerUiButtonComponent>();
    if (towerUiButtonComponent == nullptr) continue;

    towerUiButtonComponents.push_back(towerUiButtonComponent);
  }

  // sort by size
  // larger button will be rendered in the front, smaller button will be rendered in the back
  std::sort(towerUiButtonComponents.begin(), towerUiButtonComponents.end(),
    [](const TowerUiButtonComponent* c1, const TowerUiButtonComponent* c2) -> bool
  {
    return (c1->size.x * c1->size.y) < (c2->size.x * c2->size.y);
  });

  for (TowerUiButtonComponent* towerUiButtonComponent : towerUiButtonComponents) {

    // Use the program attached with the spriteComponent.
    towerUiButtonComponent->program->use();

    // Make sure to initialize glm::mat4 to the identity matrix, otherwise matrix transformations will not work.
    glm::mat4 model = glm::mat4(1.0);

    // We want to scale, rotate, then translate.
    // But since matrix operations happen from right to left, we want to code these operations in reverse order.
    model = glm::translate(model, glm::vec3(towerUiButtonComponent->position, 0.0f));

    // We want to move the origin of rotation to the center of the quad, rotate, then move the origin back.
    model = glm::translate(model, glm::vec3(0.5f * towerUiButtonComponent->size.x, 0.5f * towerUiButtonComponent->size.y, 0.0f));
    // model = glm::rotate(model, transformComponent->rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * towerUiButtonComponent->size.x, -0.5f * towerUiButtonComponent->size.y, 0.0f));

    model = glm::scale(model, glm::vec3(towerUiButtonComponent->size, 1.0f));

    towerUiButtonComponent->program->setMat4("model", model);
    towerUiButtonComponent->program->setMat4("projection", projection);
    towerUiButtonComponent->program->setVec4("spriteColor", towerUiButtonComponent->RGBA);

    // Activate texture unit 0.
    // We can have multiple texture units to use as uniforms in our shader, but we only need 1.
    glActiveTexture(GL_TEXTURE0);
    // Bind our texture so we can render it over the quad of our sprite.
    towerUiButtonComponent->texture->bind();

    // Bind our VAO which contains the quad VBO we defined and our definitions for its coordinates and texture coordinates.
    glBindVertexArray(towerUiButtonComponent->quadVAO);
    // Draw our sprite.
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
    glBindVertexArray(0);
  }
}

