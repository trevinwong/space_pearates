#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "utility.hpp"
#include "base_component.hpp"

// Contains information on how an entity should move.
class MovementComponent : public BaseComponent
{
public:
	MovementComponent(glm::vec2 accel, glm::vec2 velocity);
	~MovementComponent();

	glm::vec2 m_accel;
	glm::vec2 m_velocity;
	//Max/Min velocity are based on absolute values.
	glm::vec2 m_maxVelocity;
	glm::vec2 m_minVelocity;

	bool m_offScreenOK; // Whether or not the entity can go off screen.
	static const int typeID = MOVEMENT_COMPONENT_TYPEID;
	inline virtual int getTypeID() const { return typeID; };


	void setAcceleration(glm::vec2 accel);
	void setVelocity(glm::vec2 velocity);
	void setMaxVelocity(glm::vec2 velocity);
	void setMinVelocity(glm::vec2 velocity);

	void updateVelocity();
	void applyVelocity(glm::vec2 velocity);


};

#endif
