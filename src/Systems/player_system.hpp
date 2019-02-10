#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

// TODO: Remove unneeded includes
#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "Components/player_component.hpp"
#include "Components/movement_component.hpp"

class PlayerSystem
{
public:
	PlayerSystem();
	~PlayerSystem();

	glm::vec2 getCurrentAccel(MovementComponent *movementComponent);

	glm::vec2 getCurrentVelocity(MovementComponent *movementComponent);
	
	void interpInput(vector<shared_ptr<Entity>> entities, GLboolean keys[]);

	// Movement functions
	void walkRight(MovementComponent* mvComp);
	void walkLeft(MovementComponent* mvComp);
	void moveUp(MovementComponent* mvComp);
	void moveDown(MovementComponent* mvComp);
	void stopMovingX(MovementComponent* mvComp);
	void stopMovingY(MovementComponent* mvComp);

private:
	// Local vars
	double walkAccelSpeed = 30;
	double initWalkVelocity = 100;
	double maxWalkVelocity = 8;

};

#endif