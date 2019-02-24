#ifndef TOWER_UI_SHIFT_RIGHT_STATE_H
#define TOWER_UI_SHIFT_RIGHT_STATE_H

#include "tower_ui_state_component.hpp"
#include "tower_ui_idle_state.hpp"
#include "../../../entity_manager.hpp"
#include "../../transform_component.hpp"
#include "../build_tower_ui_component.hpp"
#include "../operate_tower_ui_component.hpp"
#include "../tower_ui_button_component.hpp"
#include "../tower_ui_button_meta_component.hpp"

#define SHIFT_RIGHT_TOTAL_TIME 0.5f // unit: s

/*
  TowerUiShiftRightState --(can only)--> TowerUiIdleState
*/
class TowerUiShiftRightState : public TowerUiStateComponent {
public:
  TowerUiShiftRightState();
  virtual void input(EntityManager& entities, GLboolean keys[]);
  virtual void update(EntityManager& entities, float dt);

  static const int typeID = ComponentType::tower_ui_state; // use same type id as parent
  inline virtual int getTypeID() const { return typeID; };
private:
  float shiftRightDuration;

  // TODO: make this function reuseable for other animations
  template<typename T>
  T computeInterpolation(T start, T end);
};

#endif // !TOWER_UI_SHIFT_RIGHT_STATE_H
