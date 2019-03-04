#include "tower_ui_idle_state.hpp"

void TowerUiIdleState::input(EntityManager &entityManager, GLboolean keys[], GLboolean keysProcessed[]) {

  vector<shared_ptr<Entity>> playerEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player}));
  vector<shared_ptr<Entity>> mapEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::map}));
  vector<shared_ptr<Entity>> towerUiEntities =
      entityManager.getEntities(entityManager.getComponentChecker(
          vector<int>{ComponentType::tower_ui_button_meta, ComponentType::tower_ui_button, ComponentType::tower_ui_state}));

  if (playerEntities.size() == 0 || mapEntities.size() == 0 || towerUiEntities.size() == 0) return;

  TransformComponent *playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();
  MapComponent *mapComponent = mapEntities[0]->getComponent<MapComponent>();
  if (playerTransformComponent == nullptr || mapComponent == nullptr) return;

  vec2 playerPosition = playerTransformComponent->position;
  vec2 playerCenterPosition = playerPosition + playerTransformComponent->size * 0.5f;

  // if the player is not at a block which can be used to build a tower or operate a tower, then
  // no response to key press
  if (!mapComponent->canBuildTowerAt(playerCenterPosition.x, playerCenterPosition.y)) return;

  TowerUiStateComponent *newState = nullptr;
  // shift ui to left
  if (keys[GLFW_KEY_A] && !keysProcessed[GLFW_KEY_A]) {
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
  else if (keys[GLFW_KEY_D] && !keysProcessed[GLFW_KEY_D]) {
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
  if ((keys[GLFW_KEY_S] || keys[GLFW_KEY_SPACE])) {
    TowerUiButtonComponent *towerUiBtn = towerUiEntities[0]->getComponent<TowerUiButtonComponent>();
    if (towerUiBtn != nullptr) {
      shared_ptr<TowerUiButtonComponent::TowerUiBtn> btn = towerUiBtn->getCurrentSelectedBtn();
      processOperate(playerCenterPosition, btn->opt, entityManager);
    }

    keys[GLFW_KEY_S] = false;
    keys[GLFW_KEY_SPACE] = false;
  }
}

void TowerUiIdleState::update(EntityManager &entityManager, float dt) {
  // let the ui follow the player
  // increase duration of current state

  vector<shared_ptr<Entity>> playerEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::player}));
  vector<shared_ptr<Entity>> mapEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::map}));
  vector<shared_ptr<Entity>> towerUiEntities =
      entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tower_ui_button, ComponentType::tower_ui_button_meta, ComponentType::tower_ui_state}));

  if (playerEntities.empty() || towerUiEntities.empty() || mapEntities.empty()) return;

  TowerUiButtonComponent *towerUiButtonComponent = towerUiEntities[0]->getComponent<TowerUiButtonComponent>();
  TowerUiButtonMetaComponent *towerUiButtonMeta = towerUiEntities[0]->getComponent<TowerUiButtonMetaComponent>();
  MapComponent *mapComponent = mapEntities[0]->getComponent<MapComponent>();
  TransformComponent *playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();

  if (towerUiButtonComponent == nullptr || towerUiButtonMeta == nullptr || playerTransformComponent == nullptr || mapComponent == nullptr) return;
  vec2 playerCenterTopPosition = vec2(playerTransformComponent->position.x + playerTransformComponent->size.x * 0.5, playerTransformComponent->position.y);
  vec2 playerCenterPosition = vec2(playerTransformComponent->position + playerTransformComponent->size * 0.5f);

  int tilePosX = (int) (playerCenterPosition.x / mapComponent->width_tile);
  int tilePosY = (int) (playerCenterPosition.y / mapComponent->height_tile);
  towerUiButtonComponent->isDisplay = mapComponent->canBuildTowerAt(tilePosX, tilePosY);

  vec2 tilePosition = vec2(tilePosX, tilePosY);
  bool isTowerHere = mapComponent->isTowerAt(tilePosX, tilePosY);

  // update tower ui opt list
  // case#1: player does nothing but swap the tower ui, then "tilePosition" and "isTowerHere" do not change, do not reset index
  // case#2: a tower was built or sold, then "isTowerHere" changed, update ui and reset index
  // case#3: the player moved to another tile, then "tilePosition" changed, update tower ui and reset index
  if (towerUiButtonComponent->tilePosition != tilePosition || towerUiButtonComponent->isTowerHere != isTowerHere) {
    towerUiButtonComponent->resetSelectedOptIndex();  // reset the index to avoid accidentally select "SELL"
    towerUiButtonComponent->tilePosition = tilePosition;
    towerUiButtonComponent->isTowerHere = isTowerHere;

    if (towerUiButtonComponent->isTowerHere) towerUiButtonComponent->setOptList(towerUiButtonMeta->towerOptList);
    else towerUiButtonComponent->setOptList(towerUiButtonMeta->buildOptList);
  }

  // Update buttons position/size/color
  vector<shared_ptr<TowerUiButtonComponent::TowerUiBtn>> btnList = towerUiButtonComponent->btnList;
  for (shared_ptr<TowerUiButtonComponent::TowerUiBtn> btn : btnList) {
    if (btn == nullptr) continue;
    switch (btn->relativeIndex) {
      case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX:
        btn->position = playerCenterTopPosition + towerUiButtonMeta->leftButtonRelativePosition;
        btn->size = towerUiButtonMeta->leftButtonSize;
        btn->RGBA = towerUiButtonMeta->leftButtonRGBA;
        btn->opt = towerUiButtonComponent->getOptListAt(towerUiButtonComponent->getSelectedOptIndex() + btn->relativeIndex);
        btn->icon = towerUiButtonMeta->getTextureByOpt(btn->opt);
        break;
      case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX:
        btn->position = playerCenterTopPosition + towerUiButtonMeta->middleButtonRelativePosition;
        btn->size = towerUiButtonMeta->middleButtonSize;
        btn->RGBA = towerUiButtonMeta->middleButtonRGBA;
        btn->opt = towerUiButtonComponent->getOptListAt(towerUiButtonComponent->getSelectedOptIndex() + btn->relativeIndex);
        btn->icon = towerUiButtonMeta->getTextureByOpt(btn->opt);
        break;
      case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX:
        btn->position = playerCenterTopPosition + towerUiButtonMeta->rightButtonRelativePosition;
        btn->size = towerUiButtonMeta->rightButtonSize;
        btn->RGBA = towerUiButtonMeta->rightButtonRGBA;
        btn->opt = towerUiButtonComponent->getOptListAt(towerUiButtonComponent->getSelectedOptIndex() + btn->relativeIndex);
        btn->icon = towerUiButtonMeta->getTextureByOpt(btn->opt);
        break;
      default:
        break;
    }
  }

  // update description
  shared_ptr<TowerUiButtonComponent::TowerUiBtn> towerUiBtn = towerUiButtonComponent->getCurrentSelectedBtn();
  if (!isTowerHere) {
    switch (towerUiBtn->opt) {
      case BUILD_FIRE_TOWER:
        towerUiButtonComponent->descriptionLine2 = "FIRE TOWER";
        towerUiButtonComponent->descriptionLine1 = "Cost 1";
        break;
      case BUILD_WATER_TOWER:
        towerUiButtonComponent->descriptionLine2 = "WATER TOWER";
        towerUiButtonComponent->descriptionLine1 = "Cost 1";
        break;
      case BUILD_LIGHT_TOWER:
        towerUiButtonComponent->descriptionLine2 = "LIGHT TOWER";
        towerUiButtonComponent->descriptionLine1 = "Cost 1";
        break;
      case BUILD_STAR_TOWER:
        towerUiButtonComponent->descriptionLine2 = "STAR TOWER";
        towerUiButtonComponent->descriptionLine1 = "Cost 1";
        break;
      case BUILD_BOOMERANG_TOWER:
        towerUiButtonComponent->descriptionLine2 = "BOOMERANG TOWER";
        towerUiButtonComponent->descriptionLine1 = "Cost 1";
        break;
      default:
        towerUiButtonComponent->descriptionLine2 = "";
        towerUiButtonComponent->descriptionLine1 = "";
        break;
    }
  } else {
    int towerId = mapComponent->getTowerIdAt(tilePosX, tilePosY);
    shared_ptr<Entity> targetTower = entityManager.getEntityById(towerId);
    // if can not find the tower by id
    if (targetTower != nullptr) {
      TowerMetaComponent *towerMetaComponent = targetTower->getComponent<TowerMetaComponent>();
      TowerAttackComponent *towerAttackComponent = targetTower->getComponent<TowerAttackComponent>();
      towerUiButtonComponent->descriptionLine2 = "";
      switch (towerUiBtn->opt) {
        case UPGRADE_TOWER_OPERATION:
          if (towerAttackComponent->currentLevel == towerAttackComponent->maxLevel) {
            towerUiButtonComponent->descriptionLine2 = "";
            towerUiButtonComponent->descriptionLine1 = "MAX Lv";
          }
          else {
            int currentLevel = towerAttackComponent->currentLevel;
            towerUiButtonComponent->descriptionLine2 = std::to_string(currentLevel) + " => " + std::to_string(currentLevel + 1) + " Lv";
            towerUiButtonComponent->descriptionLine1 = "Cost 2";
          }
          break;
        case FIX_TOWER_OPERATION:
          towerUiButtonComponent->descriptionLine2 = "FIX";
          towerUiButtonComponent->descriptionLine1 = "Cost 2";
          break;
        case SELL_TOWER_OPERATION:
          towerUiButtonComponent->descriptionLine2 = "SELL";
          towerUiButtonComponent->descriptionLine1 = "Get  1";
          break;
        default:
          towerUiButtonComponent->descriptionLine2 = "";
          towerUiButtonComponent->descriptionLine1 = "";
          break;
      }
    }
  }
  towerUiButtonComponent->descriptionLine1Pos = towerUiButtonMeta->descriptionLine1Pos + playerCenterTopPosition;
  towerUiButtonComponent->descriptionLine2Pos = towerUiButtonMeta->descriptionLine2Pos + playerCenterTopPosition;
}

void TowerUiIdleState::processOperate(glm::vec2 playerCenterPosition, TOWER_UI_OPT_TYPE operationType, EntityManager &entityManager) {
  vector<shared_ptr<Entity>> mapEntities = entityManager.getEntities(
      entityManager.getComponentChecker(vector<int>{ComponentType::map}));
  vector<shared_ptr<Entity>> playerEntities = entityManager.getEntities(
      entityManager.getComponentChecker(vector<int>{ComponentType::player, ComponentType::movement}));
  if (mapEntities.size() == 0 || playerEntities.size() == 0) return;
  MapComponent *mapComponent = mapEntities[0]->getComponent<MapComponent>();
  WalletComponent *walletComponent = playerEntities[0]->getComponent<WalletComponent>();
  if (mapComponent == nullptr || walletComponent == nullptr) return;

  float width_tile = mapComponent->width_tile;
  float height_tile = mapComponent->height_tile;
  int col = (int) (playerCenterPosition.x / mapComponent->width_tile);
  int row = (int) (playerCenterPosition.y / mapComponent->height_tile);
  if (!mapComponent->canBuildTowerAt(col, row)) return;

  // build a new tower
  if (!mapComponent->isTowerAt(col, row)) {
    glm::vec2 towerCenterBottomPosition = glm::vec2(col * width_tile + width_tile / 2.0, row * height_tile + height_tile);
    glm::vec2 towerSize = glm::vec2(40.0f, 65.0f);
    Entity towerEntity;
    switch (operationType) {
      case BUILD_FIRE_TOWER:
        towerEntity = TowerEntityFactory::createFireTower(towerCenterBottomPosition, towerSize);
        break;
      case BUILD_WATER_TOWER:
        towerEntity = TowerEntityFactory::createWaterTower(towerCenterBottomPosition, towerSize);
        break;
      case BUILD_LIGHT_TOWER:
        towerEntity = TowerEntityFactory::createLightTower(towerCenterBottomPosition, towerSize);
        break;
      case BUILD_STAR_TOWER:
        towerEntity = TowerEntityFactory::createStarTower(towerCenterBottomPosition, towerSize);
        break;
      case BUILD_BOOMERANG_TOWER:
        towerEntity = TowerEntityFactory::createBoomerangTower(towerCenterBottomPosition);
        break;
      default:
        return; // unknown type of tower
    }

    TowerMetaComponent *towerMetaComponent = towerEntity.getComponent<TowerMetaComponent>();
    if (walletComponent->spend(towerMetaComponent->buildCost)) {
      entityManager.addEntity(towerEntity);
      mapComponent->buildTowerAt(towerEntity.id, col, row);
    }
  }
  // sell/upgrade/fix a tower
  else {
    int towerId = mapComponent->getTowerIdAt(col, row);
    if (towerId == NO_TOWER_BUILD_HERE) return;
    shared_ptr<Entity> targetTower = entityManager.getEntityById(towerId);
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
        if (towerAttackComponent->currentLevel < towerAttackComponent->maxLevel)
          if (walletComponent->spend(towerMetaComponent->upgradeCost))
            towerAttackComponent->currentLevel++;
        break;
      case FIX_TOWER_OPERATION:
        break;
      default:
        return; // unknown operation
    }
  }
  // update HUD
  HUD::getInstance().resource_count = walletComponent->coins;
}