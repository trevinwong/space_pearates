#include "tower_ui_entity_factory.hpp"

Entity TowerUiEntityFactory::create()
{
  Entity towerUiEntity;

  TowerUiButtonComponent *towerUiButtonComponent = new TowerUiButtonComponent();
  TowerUiButtonMetaComponent *towerUiButtonMetaComponent = new TowerUiButtonMetaComponent();
  TowerUiStateComponent *idleState = new TowerUiIdleState();

  towerUiEntity.setComponent<TowerUiButtonComponent>(towerUiButtonComponent);
  towerUiEntity.setComponent<TowerUiButtonMetaComponent>(towerUiButtonMetaComponent);
  towerUiEntity.setComponent<TowerUiStateComponent>(idleState);

  return towerUiEntity;
}
