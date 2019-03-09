#include "tower_ui_system.hpp"

void TowerUiSystem::interpInput(EntityManager &entityManager, GLboolean keys[], GLboolean keysProcessed[]) {
  vector<shared_ptr<Entity>> towerBuildUiEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tower_ui_state}));
  if (towerBuildUiEntities.size() == 0) return;

  TowerUiStateComponent *towerUiStateComponent = towerBuildUiEntities[0]->getComponent<TowerUiStateComponent>();
  if (towerUiStateComponent == nullptr) return;

  towerUiStateComponent->input(entityManager, keys, keysProcessed);
}

void TowerUiSystem::update(EntityManager &entityManager, float dt) {
  vector<shared_ptr<Entity>> towerBuildUiEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tower_ui_state}));
  if (towerBuildUiEntities.size() == 0) return;

  // get state machine
  // because all buttons are shared one state component, get one and execute one, no need to use for loop
  TowerUiStateComponent *state = towerBuildUiEntities[0]->getComponent<TowerUiStateComponent>();
  if (state == nullptr) return;

  state->update(entityManager, dt);
}

void TowerUiSystem::render(EntityManager &entityManager, glm::mat4 projection) {
  vector<shared_ptr<Entity>> playerEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player}));
  vector<shared_ptr<Entity>> towerBuildUiEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tower_ui_button, ComponentType::tower_ui_button_meta, ComponentType::tower_ui_state}));

  if (playerEntities.size() == 0 || towerBuildUiEntities.size() == 0) return;

  TransformComponent *playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();
  TowerUiButtonComponent *towerUiButton = towerBuildUiEntities[0]->getComponent<TowerUiButtonComponent>();
  TowerUiButtonMetaComponent *towerUiButtonMeta = towerBuildUiEntities[0]->getComponent<TowerUiButtonMetaComponent>();
  if (playerTransformComponent == nullptr || towerUiButton == nullptr || towerUiButtonMeta == nullptr) return;

  glm::vec2 playerPosition = playerTransformComponent->position;
  glm::vec2 playerCenterPosition = playerPosition + playerTransformComponent->size * 0.5f;

  // if the player is not at a block which can be used to build a tower, then do not render ui
  if (!towerUiButton->isDisplay) return;

  renderTowerUiButtons(towerUiButtonMeta, towerUiButton, projection);
  renderDescription(towerUiButtonMeta, towerUiButton, projection);
}

void TowerUiSystem::renderTowerUiButtons(TowerUiButtonMetaComponent *towerUiButtonMeta, TowerUiButtonComponent *towerUiButton, glm::mat4 projection) {

  vector<shared_ptr<TowerUiButtonComponent::TowerUiBtn>> btnList = towerUiButton->btnList;
  // sort by size
  // larger button will be rendered in the front, smaller button will be rendered in the back
  std::sort(btnList.begin(), btnList.end(),
            [](const shared_ptr<TowerUiButtonComponent::TowerUiBtn> c1, const shared_ptr<TowerUiButtonComponent::TowerUiBtn> c2) -> bool {
              return (c1->size.x * c1->size.y) < (c2->size.x * c2->size.y);
            });

  towerUiButtonMeta->program->use();
  for (const shared_ptr<TowerUiButtonComponent::TowerUiBtn> btn : btnList) {
    if (btn->icon == nullptr) continue;

    // Make sure to initialize glm::mat4 to the identity matrix, otherwise matrix transformations will not work.
    glm::mat4 model = glm::mat4(1.0);

    // We want to scale, rotate, then translate.
    // But since matrix operations happen from right to left, we want to code these operations in reverse order.
    model = glm::translate(model, glm::vec3(btn->position, 0.0f));

    // We want to move the origin of rotation to the center of the quad, rotate, then move the origin back.
    model = glm::translate(model, glm::vec3(0.5f * btn->size.x, 0.5f * btn->size.y, 0.0f));
    // model = glm::rotate(model, transformComponent->rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * btn->size.x, -0.5f * btn->size.y, 0.0f));

    model = glm::scale(model, glm::vec3(btn->size, 1.0f));

    towerUiButtonMeta->program->setMat4("model", model);
    towerUiButtonMeta->program->setMat4("projection", projection);
    towerUiButtonMeta->program->setVec4("spriteColor", btn->RGBA);

    // Activate texture unit 0.
    // We can have multiple texture units to use as uniforms in our shader, but we only need 1.
    glActiveTexture(GL_TEXTURE0);
    // Bind our texture so we can render it over the quad of our sprite.
    btn->icon->bind();

    // Bind our VAO which contains the quad VBO we defined and our definitions for its coordinates and texture coordinates.
    glBindVertexArray(towerUiButtonMeta->quadVAO);
    // Draw our sprite.
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Rebind the current VAO to 0 to avoid accidentally modifying our current VAO.
    glBindVertexArray(0);
  }
}

void TowerUiSystem::renderDescription(TowerUiButtonMetaComponent *towerUiButtonMeta, TowerUiButtonComponent *towerUiButton, glm::mat4 projection){
  if(towerUiButton->descriptionLine1.size() != 0) {
    Text::getInstance().render(towerUiButton->descriptionLine1, towerUiButton->descriptionLine1Pos, 0.5, vec3(1.f, 1.f, 0.f), Font::munro_small);
  }
  if(towerUiButton->descriptionLine2.size() != 0) {
    Text::getInstance().render(towerUiButton->descriptionLine2, towerUiButton->descriptionLine2Pos, 0.5, vec3(1.f, 1.f, 0.f), Font::munro_small);
  }
}
