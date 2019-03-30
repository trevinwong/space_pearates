#ifndef TOWER_ATTACK_COMPONENT_H
#define TOWER_ATTACK_COMPONENT_H

#include "Utility/utility.hpp"
#include "../base_component.hpp"

namespace TowerTypeID {
  enum TowerTypeID {
    fire_tower,
    water_tower,
    light_tower,
    star_tower,
    boomerang_tower,
    max_count
  };
}

class TowerAttackComponent : public BaseComponent {
  public:

    // gun fire point relative position
    // e.g. if (-0.2, 0.3), then globale fire point postion = (centerX + (-0.2) * sizeWidth, centerY + (0.3) * sizeHeight)
    // Benefit: if the tower moves, then no need to update this field and the fire point position remains same
    // Note: global position
    vec2 relativeFirePosition;

    // circle radius
    float getAttackRange();

    // attack rate (unit: 1shoot very fireRate(ms))
    float getFireRate();

    // projectile attack power
    int getProjectileAttackPower();

    // Fire Rate:
    // fire rate will be initial to 0, which means the tower is ready to fire
    // After each shoot, the elapsedTimeForNextFire will be set to fireRate i.e. timeToNextFire=fireRate
    // 
    void resetElapsedTimeToNextFire();
    void reduceElapsedTimeToNextFire(float dt);
    bool isReadyForNextFire();


    static const int typeID = ComponentType::attack_tower;
    virtual int getTypeID() const { return typeID; };
    virtual int getTowerType() = 0;
    virtual void setToLevel(int level) = 0;
  protected:
    // this class is an abstract class, the constructor should not be invoked as a public function
    TowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl);
    // circle radius
    float attackRange;

    // attack rate (unit: 1shoot very fireRate(ms))
    float fireRate;

    // projectile attack power
    int projectileAttackPower;

    // time to fire again
    float elapsedTimeToNextFire;

    vector<int> attackPerLvl;
    vector<float> rangePerLvl;
    vector<float> fireRatePerLvl;
};

#endif
