#include "tower_ui_idle_state.hpp"

void TowerUiIdleState::input(EntityManager& entityManager, GLboolean keys[])
{

  vector<shared_ptr<Entity>> playerEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::player}));
  vector<shared_ptr<Entity>> mapEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::map}));
  vector<shared_ptr<Entity>> towerUiEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::build_tower_ui, ComponentType::tower_ui_button_meta, ComponentType::operate_tower_ui, ComponentType::build_tower_ui}));

  if (playerEntities.size() == 0 || mapEntities.size() == 0 || towerUiEntities.size() == 0) return;

  TransformComponent *playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();
  MapComponent *mapComponent = mapEntities[0]->getComponent<MapComponent>();
  if (playerTransformComponent == nullptr || mapComponent == nullptr) return;

  glm::vec2 playerPosition = playerTransformComponent->position;
  glm::vec2 playerCenterPosition = playerPosition + playerTransformComponent->size * 0.5f;

  // if the player is not at a block which can be used to build a tower, then
  // no response to key press
  if (!mapComponent->canBuildTowerAt(playerCenterPosition.x, playerCenterPosition.y)) return;

  TowerUiStateComponent* newState = nullptr;
  // shift ui to left
  if (keys[GLFW_KEY_A])
  {
    // set a new value
    newState = new TowerUiShiftLeftState();
    // update state
    for (shared_ptr<Entity> e : towerUiEntities) {
      e->setComponent<TowerUiStateComponent>(newState);
    }
    // state changed, delete currect state
    delete this;
  }
  // shift ui to right
  else if (keys[GLFW_KEY_D])
  {
    // set a new value
    newState = new TowerUiShiftRightState();
    // update state
    for (shared_ptr<Entity> e : towerUiEntities) {
      e->setComponent<TowerUiStateComponent>(newState);
    }
    // state changed, delete currect state
    delete this;
  }

  // create a new built tower event
  // use "keyPressTimeDuration" to avoid process one key multi-times
  if ((keys[GLFW_KEY_S] || keys[GLFW_KEY_SPACE]))
  {
    BUILD_TOWER_UI_BUTTON_TYPE operation;
    // if there is a tower
    if (mapComponent->isTowerAt(playerCenterPosition.x, playerCenterPosition.y))
    {
      OperateTowerUiComponent *operateTowerUiComponent = towerUiEntities[0]->getComponent<OperateTowerUiComponent>();
      if (operateTowerUiComponent != nullptr) {
        int index = operateTowerUiComponent->getCurrentSelectedTowerOperationListIndex();
        operation = operateTowerUiComponent->getTowerOperationListAt(index);
        processOperateNewTower(playerCenterPosition, operation, entityManager);
      }
    }
    // if no tower there
    else
    {
      BuildTowerUiComponent *buildTowerUiComponent = towerUiEntities[0]->getComponent<BuildTowerUiComponent>();
      if (buildTowerUiComponent != nullptr) {
        int index = buildTowerUiComponent->getCurrentSelectedTowerTypeListIndex();
        operation = buildTowerUiComponent->getTowerTypeListAt(index);
        processBuildNewTower(playerCenterPosition, operation, entityManager);
      }
    }
    keys[GLFW_KEY_S] = false;
    keys[GLFW_KEY_SPACE] = false;
  }
}

void TowerUiIdleState::update(EntityManager& entityManager, float dt)
{
  // let the ui follow the player
  // increase duration of current state

  vector<shared_ptr<Entity>> playerEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::player}));
  vector<shared_ptr<Entity>> towerUiEntities =
    entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::build_tower_ui, ComponentType::tower_ui_button_meta, ComponentType::operate_tower_ui, ComponentType::build_tower_ui}));

  if (playerEntities.size() == 0 || towerUiEntities.size() == 0) return;

  TowerUiButtonMetaComponent *towerUiButtonMetaComponent = towerUiEntities[0]->getComponent<TowerUiButtonMetaComponent>();
  TransformComponent *playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();

  if (towerUiButtonMetaComponent == nullptr || playerTransformComponent == nullptr) return;
  glm::vec2 playerCenterTopPosition = glm::vec2(playerTransformComponent->position.x + playerTransformComponent->size.x * 0.5, playerTransformComponent->position.y);

  for (shared_ptr<Entity> towerUiEntity : towerUiEntities) {
    TowerUiButtonComponent *towerUiButtonComponent = towerUiEntity->getComponent<TowerUiButtonComponent>();
    if (towerUiButtonComponent == nullptr) continue;

    // Update buttons position/size/color
    switch (towerUiButtonComponent->relativeIndex) {
    case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX:   // left -> right
      towerUiButtonComponent->position = playerCenterTopPosition + towerUiButtonMetaComponent->leftButtonRelativePosition;
      towerUiButtonComponent->size = towerUiButtonMetaComponent->leftButtonSize;
      towerUiButtonComponent->RGBA = towerUiButtonMetaComponent->leftButtonRGBA;
      break;
    case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> left
      towerUiButtonComponent->position = playerCenterTopPosition + towerUiButtonMetaComponent->middleButtonRelativePosition;
      towerUiButtonComponent->size = towerUiButtonMetaComponent->middleButtonSize;
      towerUiButtonComponent->RGBA = towerUiButtonMetaComponent->middleButtonRGBA;
      break;
    case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX: // right -> middle
      towerUiButtonComponent->position = playerCenterTopPosition + towerUiButtonMetaComponent->rightButtonRelativePosition;
      towerUiButtonComponent->size = towerUiButtonMetaComponent->rightButtonSize;
      towerUiButtonComponent->RGBA = towerUiButtonMetaComponent->rightButtonRGBA;
      break;
    default:
      break;
    }
  }
}

void TowerUiIdleState::processBuildNewTower(glm::vec2 playerCenterPosition, BUILD_TOWER_UI_BUTTON_TYPE operationType, EntityManager& entityManager)
{
  vector<shared_ptr<Entity>> mapEntities = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::map}));
  vector<shared_ptr<Entity>> playerEntities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player, ComponentType::movement}));
  if (mapEntities.size() == 0 || playerEntities.size() == 0) return;
  MapComponent *mapComponent = mapEntities[0]->getComponent<MapComponent>();
  WalletComponent *walletComponent = playerEntities[0]->getComponent<WalletComponent>();
  if (mapComponent == nullptr || walletComponent == nullptr) return;

  float width_tile = mapComponent->width_tile;
  float height_tile = mapComponent->height_tile;
  int col = (int)(playerCenterPosition.x / mapComponent->width_tile);
  int row = (int)(playerCenterPosition.y / mapComponent->height_tile);

  // build a new tower
  if (mapComponent->canBuildTowerAt(col, row) && !mapComponent->isTowerAt(col, row)) {
    glm::vec2 towerCenterBottomPosition = glm::vec2(col*width_tile + width_tile / 2.0, row*height_tile + height_tile);
    glm::vec2 towerSize = glm::vec2(40.0f, 65.0f);
    Entity towerEntity;
    switch (operationType) {
    case BUILD_FIRE_TOWER:
      towerEntity = TowerEntityFactory::createFireTower(towerCenterBottomPosition, towerSize);
      break;
    case BUILD_LIGHT_TOWER:
      towerEntity = TowerEntityFactory::createLightTower(towerCenterBottomPosition, towerSize);
      break;
    case BUILD_STAR_TOWER:
      towerEntity = TowerEntityFactory::createStarTower(towerCenterBottomPosition, towerSize);
      break;
    default:
      return; // unknown type of tower
    }

    TowerMetaComponent *towerMetaComponent = towerEntity.getComponent<TowerMetaComponent>();
    if (walletComponent->spend(towerMetaComponent->buildCost)) {
      entityManager.addEntity(towerEntity);
      mapComponent->buildTowerAt(towerEntity.id, col, row);     
    }
    else {
      // TODO: tell player not enough money
      // TODO: not enough money, so destroy towerEntity
    }
    // update HUD
    HUD::getInstance().resource_count = walletComponent->coins;
  }
}


void TowerUiIdleState::processOperateNewTower(glm::vec2 playerCenterPosition, BUILD_TOWER_UI_BUTTON_TYPE operationType, EntityManager& entityManager)
{
  vector<shared_ptr<Entity>> mapEntities = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::map}));
  vector<shared_ptr<Entity>> playerEntities = entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player, ComponentType::movement}));
  if (mapEntities.size() == 0 || playerEntities.size() == 0) return;
  MapComponent *mapComponent = mapEntities[0]->getComponent<MapComponent>();
  WalletComponent *walletComponent = playerEntities[0]->getComponent<WalletComponent>();
  if (mapComponent == nullptr || walletComponent == nullptr) return;

  float width_tile = mapComponent->width_tile;
  float height_tile = mapComponent->height_tile;
  int col = (int)(playerCenterPosition.x / mapComponent->width_tile);
  int row = (int)(playerCenterPosition.y / mapComponent->height_tile);

  // sell/upgrade/fix a tower
  if (mapComponent->canBuildTowerAt(col, row) && mapComponent->isTowerAt(col, row))
  {
    int towerId = mapComponent->getTowerIdAt(col, row);
    if (towerId == NO_TOWER_BUILD_HERE) return;

    // find the tower by entity id
    vector<shared_ptr<Entity>> towerEntities = entityManager.getEntities(entityManager.getComponentChecker(vector<int> {ComponentType::tower_meta}));
    shared_ptr<Entity> targetTower;
    for (shared_ptr<Entity> e : towerEntities) {
      if (e->id == towerId) {
        targetTower = e;
        break;
      }
    }
    // if can not find the tower by id
    if (targetTower == nullptr) return;
    TowerMetaComponent *towerMetaComponent = targetTower->getComponent<TowerMetaComponent>();
    TowerAttackComponent *towerAttackComponent = targetTower->getComponent<TowerAttackComponent>();

    switch (operationType) {
    case SELL_TOWER_OPERATION:
      walletComponent->earn(towerMetaComponent->sellGet);
      entityManager.removeEntity(targetTower);
      mapComponent->removeTowerAt(col, row);
      break;
    case UPGRADE_TOWER_OPERATION:
      if (towerAttackComponent->currentLevel < towerAttackComponent->maxLevel) {
        if (walletComponent->spend(towerMetaComponent->upgradeCost)) {
          towerAttackComponent->currentLevel++;
        }
      }
      break;
    case FIX_TOWER_OPERATION:
      break;
    default:
      return; // unknown operation
    }
    // update HUD
    HUD::getInstance().resource_count = walletComponent->coins;
  }
}