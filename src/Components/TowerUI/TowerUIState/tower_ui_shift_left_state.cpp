#include "tower_ui_shift_left_state.hpp"

TowerUiShiftLeftState::TowerUiShiftLeftState() :
  shiftLeftDuration(0.0f)
{
}

void TowerUiShiftLeftState::input(EntityManager& entityManager, GLboolean keys[])
{
  // curretly in the middle of shift left state, cannot change state
  return;
}

void TowerUiShiftLeftState::update(EntityManager& entityManager, float dt)
{
  // increase duration of current state
  shiftLeftDuration += dt;

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
      towerUiButtonComponent->position = playerCenterTopPosition + computeInterpolation(towerUiButtonMetaComponent->leftButtonRelativePosition, towerUiButtonMetaComponent->rightButtonRelativePosition);
      towerUiButtonComponent->size = computeInterpolation(towerUiButtonMetaComponent->leftButtonSize, towerUiButtonMetaComponent->rightButtonSize);
      towerUiButtonComponent->RGBA = computeInterpolation(towerUiButtonMetaComponent->leftButtonRGBA, towerUiButtonMetaComponent->rightButtonRGBA);
      break;
    case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> left
      towerUiButtonComponent->position = playerCenterTopPosition + computeInterpolation(towerUiButtonMetaComponent->middleButtonRelativePosition, towerUiButtonMetaComponent->leftButtonRelativePosition);
      towerUiButtonComponent->size = computeInterpolation(towerUiButtonMetaComponent->middleButtonSize, towerUiButtonMetaComponent->leftButtonSize);
      towerUiButtonComponent->RGBA = computeInterpolation(towerUiButtonMetaComponent->middleButtonRGBA, towerUiButtonMetaComponent->leftButtonRGBA);
      break;
    case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX: // right -> middle
      towerUiButtonComponent->position = playerCenterTopPosition + computeInterpolation(towerUiButtonMetaComponent->rightButtonRelativePosition, towerUiButtonMetaComponent->middleButtonRelativePosition);
      towerUiButtonComponent->size = computeInterpolation(towerUiButtonMetaComponent->rightButtonSize, towerUiButtonMetaComponent->middleButtonSize);
      towerUiButtonComponent->RGBA = computeInterpolation(towerUiButtonMetaComponent->rightButtonRGBA, towerUiButtonMetaComponent->middleButtonRGBA);
      break;
    default:
      break;
    }
  }

  // if touch the end of state
  // then finish current state and move to next state
  if (shiftLeftDuration >= SHIFT_LEFT_TOTAL_TIME) {
    // update index
    BuildTowerUiComponent *buildTowerUiComponent = towerUiEntities[0]->getComponent<BuildTowerUiComponent>();
    OperateTowerUiComponent *operateTowerUiComponent = towerUiEntities[0]->getComponent<OperateTowerUiComponent>();

    // shift buttons to left == move index to right
    if (buildTowerUiComponent != nullptr) buildTowerUiComponent->moveRightCurrentSelectedTowerTypeListIndex();
    if (operateTowerUiComponent != nullptr) operateTowerUiComponent->moveRightCurrentSelectedTowerOperationListIndex();

    // update relative index
    for (shared_ptr<Entity> towerUiEntity : towerUiEntities) {
      TowerUiButtonComponent *towerUiButtonComponent = towerUiEntity->getComponent<TowerUiButtonComponent>();
      if (towerUiButtonComponent == nullptr) continue;

      switch (towerUiButtonComponent->relativeIndex) {
      case LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX:   // left -> right
        towerUiButtonComponent->relativeIndex = RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX;
        break;
      case MIDDLE_TOWER_UI_BUTTON_RELATIVE_INDEX: // middle -> left
        towerUiButtonComponent->relativeIndex = LEFT_TOWER_UI_BUTTON_RELATIVE_INDEX; 
        break;
      case RIGHT_TOWER_UI_BUTTON_RELATIVE_INDEX: // right -> middle
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
    // new state created and pointed, delete currect state
    delete this;
  }
}

template<typename T>
inline T TowerUiShiftLeftState::computeInterpolation(T start, T end)
{
  if (shiftLeftDuration >= SHIFT_LEFT_TOTAL_TIME) return end;
  if (shiftLeftDuration <= 0) return start;

  T result = (shiftLeftDuration / SHIFT_LEFT_TOTAL_TIME) * end + (SHIFT_LEFT_TOTAL_TIME - shiftLeftDuration) / SHIFT_LEFT_TOTAL_TIME * start;
  return result;
}
