#ifndef TOWER_UI_STATE_COMPONENT_H
#define TOWER_UI_STATE_COMPONENT_H

#include "../../../Utility/utility.hpp"
#include "../../../entity_manager.hpp"
#include "../../base_component.hpp"

class TowerUiStateComponent : public BaseComponent {
  public:
    // Note:
    // In ECS architecture, components can only contain data, such as position, size, health points etc.
    // Here we use state machine, the function declared here can be considered as variables to indicate current state
    // These functions are called only by systems, so not violate ECS architecture

    // An alternative method is to use StateComponent stores current state which can be int or char type.
    // However, if using this method, there will be a "long" switch block (or if-else block) in the correlated system.
    virtual void input(EntityManager& entities, GLboolean keys[], GLboolean keysProcessed[]) {};
    virtual void update(EntityManager& entities, float dt) {};

    static const int typeID = ComponentType::tower_ui_state; // all child classes use same type id
    inline virtual int getTypeID() const { return typeID; };
  protected:
    float duration;
    float totalTime;

    glm::vec4 computeLinearInterpolation(glm::vec4 start, glm::vec4 end);
    // p1->p2->p3->p1
    vec2 computeCatmullRomInterpolation(vec2 p1, vec2 p2, vec2 p3);
    // p1->p2->p3->p4
    // Note: from cpsc426, p1 and p4 are used to compute the direction for p2 and p3.
    // when t=0, result=p2
    // when t=1, result=p3
    vec2 computeCatmullRomInterpolation(vec2 p1, vec2 p2, vec2 p3, vec2 p4);
};

#endif // !STATE_SYSTEM
