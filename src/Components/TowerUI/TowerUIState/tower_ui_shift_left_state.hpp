#ifndef TOWER_UI_SHIFT_LEFT_STATE_H
#define TOWER_UI_SHIFT_LEFT_STATE_H

#include "../../../entity_manager.hpp"
#include "../../transform_component.hpp"
#include "../tower_ui_button_component.hpp"
#include "../tower_ui_button_meta_component.hpp"
#include "tower_ui_idle_state.hpp"
#include "tower_ui_state_component.hpp"

#define SHIFT_LEFT_TOTAL_TIME 0.2f // unit: s

/*
  TowerUiShiftLeftState --(can only)--> TowerUiIdleState
*/
class TowerUiShiftLeftState : public TowerUiStateComponent {
public:
  TowerUiShiftLeftState();
  virtual void input(EntityManager& entities, GLboolean keys[], GLboolean keysProcessed[]);
  virtual void update(EntityManager& entities, float dt);

  static const int typeID = ComponentType::tower_ui_state; // use same type id as parent
  inline virtual int getTypeID() const { return typeID; };
};

#endif
