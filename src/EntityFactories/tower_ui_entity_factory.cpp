#include "tower_ui_entity_factory.hpp"

Entity TowerUiEntityFactory::create()
{
  shared_ptr<TowerUiButtonComponent> towerUiButtonComponent = make_shared<TowerUiButtonComponent>();
  shared_ptr<TowerUiButtonMetaComponent> towerUiButtonMetaComponent = make_shared<TowerUiButtonMetaComponent>();
  shared_ptr<TowerUiStateComponent> idleState = make_shared<TowerUiIdleState>();

  Entity towerUiEntity;
  towerUiEntity.setComponent<TowerUiButtonComponent>(towerUiButtonComponent);
  towerUiEntity.setComponent<TowerUiButtonMetaComponent>(towerUiButtonMetaComponent);
  towerUiEntity.setComponent<TowerUiStateComponent>(idleState);
  return towerUiEntity;
}
