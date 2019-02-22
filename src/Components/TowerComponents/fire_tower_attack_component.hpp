#ifndef FIRE_TOWER_ATTACK_COMPONENT_H
#define FIRE_TOWER_ATTACK_COMPONENT_H

#include "utility.hpp"
#include "../base_component.hpp"
#include "tower_attack_component.hpp"

class FireTowerAttackComponent : public TowerAttackComponent {
public:
  // Note: _shootRate (unit: s)
  FireTowerAttackComponent(glm::vec2 _relativeFirePosition, float _attackRange, int _maxLevel, float _fireRate, int projectileAttackPower);

  // Fire Rate:
  // fire rate will be initial to 0, which means the tower is ready to fire
  // After each shoot, the elapsedTimeForNextFire will be set to fireRate i.e. timeToNextFire=fireRate
  // 
  float getElapsedTimeToNextFire();
  void resetElapsedTimeToNextFire();
  void reduceElapsedTimeToNextFire(float dt);
  bool isReadyForNextFire();
  float getFireRate();
  
  int getProjectileAttackPower();

  static const int typeID = ComponentType::fire_tower;
  virtual int getTypeID() const { return typeID; };

private:

  // time to fire again
  float elapsedTimeToNextFire;

  // attack rate (unit: 1shoot very fireRate(ms))
  float fireRate;

  // projectile attack power
  int projectileAttackPower;
};

#endif
