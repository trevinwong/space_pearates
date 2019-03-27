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

  shared_ptr<TransformComponent> playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();
  shared_ptr<MapComponent> mapComponent = mapEntities[0]->getComponent<MapComponent>();
  if (playerTransformComponent == nullptr || mapComponent == nullptr) return;

  vec2 playerPosition = playerTransformComponent->position;
  vec2 playerCenterPosition = playerPosition + playerTransformComponent->size * 0.5f;

  // if the player is not at a block which can be used to build a tower or operate a tower, then
  // no response to key press
  if (!mapComponent->canBuildTowerAt(playerCenterPosition.x, playerCenterPosition.y)) return;

  shared_ptr<TowerUiStateComponent> newState;
  // shift ui to left
  if (keys[GLFW_KEY_A] && !keysProcessed[GLFW_KEY_A]) {
    // set a new value
    newState = make_shared<TowerUiShiftLeftState>();
    // update state
    for (shared_ptr<Entity> e : towerUiEntities) {
      e->setComponent<TowerUiStateComponent>(newState);
    }
    // state changed, delete currect state
    // the deletion will be handled by smart pointer
  }
    // shift ui to right
  else if (keys[GLFW_KEY_D] && !keysProcessed[GLFW_KEY_D]) {
    // set a new value
    newState = make_shared<TowerUiShiftRightState>();
    // update state
    for (shared_ptr<Entity> e : towerUiEntities) {
      e->setComponent<TowerUiStateComponent>(newState);
    }
    // state changed, delete currect state
    // the deletion will be handled by smart pointer
  }

  // create a new built tower event
  // use "keyPressTimeDuration" to avoid process one key multi-times
  if ((keys[GLFW_KEY_S] || keys[GLFW_KEY_SPACE])) {
    shared_ptr<TowerUiButtonComponent> towerUiBtn = towerUiEntities[0]->getComponent<TowerUiButtonComponent>();
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

  shared_ptr<TowerUiButtonComponent> towerUiButtonComponent = towerUiEntities[0]->getComponent<TowerUiButtonComponent>();
  shared_ptr<TowerUiButtonMetaComponent> towerUiButtonMeta = towerUiEntities[0]->getComponent<TowerUiButtonMetaComponent>();
  shared_ptr<MapComponent> mapComponent = mapEntities[0]->getComponent<MapComponent>();
  shared_ptr<TransformComponent> playerTransformComponent = playerEntities[0]->getComponent<TransformComponent>();

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
  shared_ptr<TowerData> data;
  if (!isTowerHere) {
    switch (towerUiBtn->opt) {
      case BUILD_FIRE_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_FIRE_TOWER];
        towerUiButtonComponent->descriptionLine2 = "FIRE TOWER";
        break;
      case BUILD_WATER_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_WATER_TOWER];
        towerUiButtonComponent->descriptionLine2 = "WATER TOWER";
        break;
      case BUILD_LIGHT_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_LIGHT_TOWER];
        towerUiButtonComponent->descriptionLine2 = "LIGHT TOWER";
        break;
      case BUILD_STAR_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_STAR_TOWER];
        towerUiButtonComponent->descriptionLine2 = "STAR TOWER";
        break;
      case BUILD_BOOMERANG_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_BOOMERANG_TOWER];
        towerUiButtonComponent->descriptionLine2 = "BOOMERANG TOWER";
        break;
      default:
		
        towerUiButtonComponent->descriptionLine2 = "";
        towerUiButtonComponent->descriptionLine1 = "";
        break;
    }
    towerUiButtonComponent->descriptionLine1 = "Cost " + std::to_string(data->buildCost);
  } else {
    int towerId = mapComponent->getTowerIdAt(tilePosX, tilePosY);
    shared_ptr<Entity> targetTower = entityManager.getEntityById(towerId);
    // if can not find the tower by id
    if (targetTower != nullptr) {
      shared_ptr<TowerMetaComponent> towerMetaComponent = targetTower->getComponent<TowerMetaComponent>();
      shared_ptr<TowerAttackComponent> towerAttackComponent = targetTower->getComponent<TowerAttackComponent>();
      towerUiButtonComponent->descriptionLine2 = "";
      switch (towerUiBtn->opt) {
        case UPGRADE_TOWER_OPERATION:
          if (towerMetaComponent->currentLevel == towerMetaComponent->maxLevel) {
            towerUiButtonComponent->descriptionLine2 = "";
            towerUiButtonComponent->descriptionLine1 = "MAX Lv";
          }
          else {
            int currentLevel = towerMetaComponent->currentLevel;
            towerUiButtonComponent->descriptionLine2 = std::to_string(currentLevel) + " => " + std::to_string(currentLevel + 1) + " Lv";
            towerUiButtonComponent->descriptionLine1 = "Cost " + std::to_string(towerMetaComponent->upgradeCostsPerLvl[currentLevel+1]); 
          }
          break;
        case FIX_TOWER_OPERATION:
          towerUiButtonComponent->descriptionLine2 = "FIX";
          towerUiButtonComponent->descriptionLine1 = "Cost 2";
          break;
        case SELL_TOWER_OPERATION:
          towerUiButtonComponent->descriptionLine2 = "SELL";
          towerUiButtonComponent->descriptionLine1 = "Get " + std::to_string(towerMetaComponent->getSellMoney());
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
  vector<shared_ptr<Entity>> towerUiEntities =
	  entityManager.getEntities(entityManager.getComponentChecker(vector<int>{ComponentType::tower_ui_button, ComponentType::tower_ui_button_meta, ComponentType::tower_ui_state}));
  if (mapEntities.size() == 0 || playerEntities.size() == 0 || towerUiEntities.size() == 0) return;
  shared_ptr<MapComponent> mapComponent = mapEntities[0]->getComponent<MapComponent>();
  shared_ptr<WalletComponent> walletComponent = playerEntities[0]->getComponent<WalletComponent>();
  shared_ptr<TowerUiButtonComponent> towerUiButtonComponent = towerUiEntities[0]->getComponent<TowerUiButtonComponent>();
  if (mapComponent == nullptr || walletComponent == nullptr) return;

  float width_tile = mapComponent->width_tile;
  float height_tile = mapComponent->height_tile;
  int col = (int) (playerCenterPosition.x / mapComponent->width_tile);
  int row = (int) (playerCenterPosition.y / mapComponent->height_tile);
  if (!mapComponent->canBuildTowerAt(col, row)) return;

  

  // build a new tower
  if (!mapComponent->isTowerAt(col, row)) {
    shared_ptr<TowerData> data;
    switch (operationType) {
      case BUILD_FIRE_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_FIRE_TOWER];
        break;
      case BUILD_WATER_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_WATER_TOWER];
        break;
      case BUILD_LIGHT_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_LIGHT_TOWER];
        break;
      case BUILD_STAR_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_STAR_TOWER];
        break;
      case BUILD_BOOMERANG_TOWER:
        data = TowerDataLoader::allTowerData[BUILD_BOOMERANG_TOWER];
        break;
      default:
        return; // unknown type of tower
    }

	if (walletComponent->spend(data->buildCost)) {
		towerUiButtonComponent->descriptionLine1Color = towerUiButtonComponent->defaultTextColor;
		glm::vec2 towerCenterBottomPosition = glm::vec2(col * width_tile + width_tile / 2.0, row * height_tile + height_tile);
		glm::vec2 towerSize = glm::vec2(40.0f, 65.0f) * SCALING_FACTOR;
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
			towerEntity = TowerEntityFactory::createBoomerangTower(towerCenterBottomPosition, towerSize);
			break;
		default:
			return; // unknown type of tower
		}
		Mix_PlayChannel(-1, AudioLoader::getInstance().build_tower, 0);
		entityManager.addEntity(towerEntity);
		mapComponent->buildTowerAt(towerEntity.id, col, row);
	}
	else
	{
		Mix_PlayChannel(-1, AudioLoader::getInstance().invalid, 0);
		towerUiButtonComponent->descriptionLine1Color = towerUiButtonComponent->noMoneyTextColor;
	}
  }
  // sell/upgrade/fix a tower
  else {
    int towerId = mapComponent->getTowerIdAt(col, row);
    if (towerId == NO_TOWER_BUILD_HERE) return;
    shared_ptr<Entity> targetTower = entityManager.getEntityById(towerId);
    // if can not find the tower by id
    if (targetTower == nullptr) return;
    shared_ptr<TowerMetaComponent> towerMetaComponent = targetTower->getComponent<TowerMetaComponent>();
    shared_ptr<TowerAttackComponent> towerAttackComponent = targetTower->getComponent<TowerAttackComponent>();

	switch (operationType) {
	case SELL_TOWER_OPERATION:
		Mix_PlayChannel(-1, AudioLoader::getInstance().sell_tower, 0);
		walletComponent->earn(towerMetaComponent->getSellMoney());
		entityManager.removeEntity(targetTower);
		mapComponent->removeTowerAt(col, row);
		break;
	case UPGRADE_TOWER_OPERATION:
		if (towerMetaComponent->currentLevel < towerMetaComponent->maxLevel)
		{
			// upgradeCostsPerLvl describe how much money it costs to upgrade TO that level
			if (walletComponent->spend(towerMetaComponent->upgradeCostsPerLvl[towerMetaComponent->currentLevel + 1])) {
				Mix_PlayChannel(-1, AudioLoader::getInstance().upgrade_tower, 0);
				towerUiButtonComponent->descriptionLine1Color = towerUiButtonComponent->defaultTextColor;
				towerMetaComponent->totalWorth += towerMetaComponent->upgradeCostsPerLvl[towerMetaComponent->currentLevel + 1];
				towerMetaComponent->currentLevel += 1;
				towerAttackComponent->setToLevel(towerMetaComponent->currentLevel);
			}
			else
			{
				Mix_PlayChannel(-1, AudioLoader::getInstance().invalid, 0);
				towerUiButtonComponent->descriptionLine1Color = towerUiButtonComponent->noMoneyTextColor;
			}
		}
		else
		{
			Mix_PlayChannel(-1, AudioLoader::getInstance().invalid, 0);
			towerUiButtonComponent->descriptionLine1Color = towerUiButtonComponent->noMoneyTextColor;
		}
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
