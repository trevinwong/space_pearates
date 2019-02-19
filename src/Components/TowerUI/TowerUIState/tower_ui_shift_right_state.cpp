#include "tower_ui_shift_right_state.hpp"

TowerUiShiftRightState::TowerUiShiftRightState():
  shiftRightDuration(0.0)
{
}

void TowerUiShiftRightState::input(EntityManager& entityManager, GLboolean keys[])
{
  // curretly in the middle of shift right state, cannot change state
  return;
}

void TowerUiShiftRightState::update(EntityManager& entityManager, float dt)
{
  // increase duration of current state
  shiftRightDuration += dt;

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
    case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX:   // left -> middle
      towerUiButtonComponent->position = playerCenterTopPosition + computeInterpulation(towerUiButtonMetaComponent->leftButtonRelativePosition, towerUiButtonMetaComponent->middleButtonRelativePosition);
      towerUiButtonComponent->size = computeInterpulation(towerUiButtonMetaComponent->leftButtonSize, towerUiButtonMetaComponent->middleButtonSize);
      towerUiButtonComponent->RGBA = computeInterpulation(towerUiButtonMetaComponent->leftButtonRGBA, towerUiButtonMetaComponent->middleButtonRGBA);
      break;
    case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> right
      towerUiButtonComponent->position = playerCenterTopPosition + computeInterpulation(towerUiButtonMetaComponent->middleButtonRelativePosition, towerUiButtonMetaComponent->rightButtonRelativePosition);
      towerUiButtonComponent->size = computeInterpulation(towerUiButtonMetaComponent->middleButtonSize, towerUiButtonMetaComponent->rightButtonSize);
      towerUiButtonComponent->RGBA = computeInterpulation(towerUiButtonMetaComponent->middleButtonRGBA, towerUiButtonMetaComponent->rightButtonRGBA);
      break;
    case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX: // right -> left
      towerUiButtonComponent->position = playerCenterTopPosition + computeInterpulation(towerUiButtonMetaComponent->rightButtonRelativePosition, towerUiButtonMetaComponent->leftButtonRelativePosition);
      towerUiButtonComponent->size = computeInterpulation(towerUiButtonMetaComponent->rightButtonSize, towerUiButtonMetaComponent->leftButtonSize);
      towerUiButtonComponent->RGBA = computeInterpulation(towerUiButtonMetaComponent->rightButtonRGBA, towerUiButtonMetaComponent->leftButtonRGBA);
      break;
    default:
      break;
    }
  }

  // if touch the end of state
  // then finish current state and move to next state
  if (shiftRightDuration >= SHIFT_RIGHT_TOTAL_TIME) {
    // update index
    BuildTowerUiComponent *buildTowerUiComponent = towerUiEntities[0]->getComponent<BuildTowerUiComponent>();
    OperateTowerUiComponent *operateTowerUiComponent = towerUiEntities[0]->getComponent<OperateTowerUiComponent>();

    // shift buttons to right == move index to left
    if (buildTowerUiComponent != nullptr) buildTowerUiComponent->moveLeftCurrentSelectedTowerTypeListIndex();
    if (operateTowerUiComponent != nullptr) operateTowerUiComponent->moveLeftCurrentSelectedTowerOperationListIndex();

    // update relative index
    for (shared_ptr<Entity> towerUiEntity : towerUiEntities) {
      TowerUiButtonComponent *towerUiButtonComponent = towerUiEntity->getComponent<TowerUiButtonComponent>();
      if (towerUiButtonComponent == nullptr) continue;

      switch (towerUiButtonComponent->relativeIndex) {
      case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX:   // right -> left
        towerUiButtonComponent->relativeIndex = LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX;
        break;
      case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> right
        towerUiButtonComponent->relativeIndex = RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX;
        break;
      case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX: // left -> middle
        towerUiButtonComponent->relativeIndex = MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX;
        break;
      default:
        break;
      }
    }

    // create a new state
    TowerUiStateComponent* newState = new TowerUiIdleState();
    // update state
    for (shared_ptr<Entity> e : towerUiEntities) {
      e->setComponent<TowerUiStateComponent>(newState);
    }
    // towerUiStateSystem pointer points to new instace, delete currect state
    delete this;
  }
}



template<typename T>
inline T TowerUiShiftRightState::computeInterpulation(T start, T end)
{
  if (shiftRightDuration >= SHIFT_RIGHT_TOTAL_TIME) return end;
  if (shiftRightDuration <= 0) return start;

  T result = (shiftRightDuration / SHIFT_RIGHT_TOTAL_TIME) * end + (SHIFT_RIGHT_TOTAL_TIME - shiftRightDuration) / SHIFT_RIGHT_TOTAL_TIME * start;
  return result;
}
