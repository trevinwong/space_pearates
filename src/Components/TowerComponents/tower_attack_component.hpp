#ifndef TOWER_ATTACK_COMPONENT_H
#define TOWER_ATTACK_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"

class TowerAttackComponent : public BaseComponent {
  public:
    glm::vec2 getRelativeFirePosition();
    int getAttackRange();
    int getCurrentLevel();
    int getMaxLevel();

    virtual int getTypeID() const = 0;

  protected:
    // this class is an abstract class, the constructor should not be invoked as a public function
    TowerAttackComponent(glm::vec2 _relativeFirePosition, float _attackRange, int _maxLevel);
    ~TowerAttackComponent();

  private:
    // gun fire point relative position
    // e.g. if (-0.2, 0.3), then globale fire point postion = (centerX + (-0.2) * sizeWidth, centerY + (0.3) * sizeHeight)
    // Benefit: if the tower moves, then no need to update this field and the fire point position remains same
    // Note: global position
    glm::vec2 relativeFirePosition;

    // circle radius
    float attackRange;

    // current level
    int currentLevel;

    // max level
    int maxLevel;
};

#endif