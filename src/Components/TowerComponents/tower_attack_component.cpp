#include "tower_attack_component.hpp"

TowerAttackComponent::TowerAttackComponent(vec2 _relativeFirePosition, vector<int> _attackPerLvl, vector<float> _rangePerLvl, vector<float> _fireRatePerLvl) :
  relativeFirePosition(_relativeFirePosition),
  attackPerLvl(_attackPerLvl),
  rangePerLvl(_rangePerLvl),
  fireRatePerLvl(_fireRatePerLvl) 
{
  elapsedTimeToNextFire = 0;
}

void TowerAttackComponent::resetElapsedTimeToNextFire()
{
  elapsedTimeToNextFire = getFireRate();
}

void TowerAttackComponent::reduceElapsedTimeToNextFire(float dt)
{
  // If the tower is already ready, then no need to reduce elapsed time
  if (isReadyForNextFire()) return;

  elapsedTimeToNextFire -= dt;
}

bool TowerAttackComponent::isReadyForNextFire()
{
  return elapsedTimeToNextFire <= 0.0;
}

shared_ptr<Texture> TowerAttackComponent::getLevelTexture(int level)
{
	if (level < towerTextures.size())
	{
		return towerTextures[level];
	}
	else
	{
		//Safeguard in-case texture is not found.
		return towerTextures[0];
	}
	
}

float TowerAttackComponent::getAttackRange()
{
  return attackRange;
}

float TowerAttackComponent::getFireRate()
{
  return this->fireRate;
}

int TowerAttackComponent::getProjectileAttackPower()
{
  return this->projectileAttackPower;
}
