#include "movement_component.hpp"

MovementComponent::MovementComponent(glm::vec2 accel, glm::vec2 velocity)
{
	m_accel = accel;
	m_velocity = velocity;
	m_maxVelocity = glm::vec2(999999,999999);
	m_minVelocity = glm::vec2(0, 0);
}

void MovementComponent::setAcceleration(glm::vec2 accel)
{
	m_accel = accel;
}

void MovementComponent::setVelocity(glm::vec2 velocity)
{
	m_velocity = velocity;
}

void MovementComponent::setMaxVelocity(glm::vec2 velocity)
{
	m_maxVelocity = velocity;
}

void MovementComponent::setMinVelocity(glm::vec2 velocity)
{
	m_minVelocity = velocity;
}

void MovementComponent::updateVelocity()
{
	m_velocity += m_accel;

	// If the updated velocity exceeds the max velocity...
	if (abs(m_velocity.x) > m_maxVelocity.x)
	{
		// If the velocity is negative...
		if (m_velocity.x < 0)
		{
			m_velocity.x = -m_maxVelocity.x;
		}
		else
		{
			m_velocity.x = m_maxVelocity.x;
		}
	}

	if (abs(m_velocity.y) > m_maxVelocity.y)
	{
		if (m_velocity.y < 0)
		{
			m_velocity.y = -m_maxVelocity.y;
		}
		else
		{
			m_velocity.y = m_maxVelocity.y;
		}
	}

	// Check for minVelocity too
	if (abs(m_velocity.x) < m_minVelocity.x)
	{
		// If the velocity is negative...
		if (m_velocity.x < 0)
		{
			m_velocity.x = -m_minVelocity.x;
		}
		else
		{
			m_velocity.x = m_minVelocity.x;
		}
	}

	if (abs(m_velocity.y) < m_minVelocity.y)
	{
		// If the velocity is negative...
		if (m_velocity.y < 0)
		{
			m_velocity.y = -m_minVelocity.y;
		}
		else
		{
			m_velocity.y = m_minVelocity.y;
		}
	}

}

// Directly applies a velocity to this entity's current velocity.
void MovementComponent::applyVelocity(glm::vec2 velocity)
{
	m_velocity += velocity;
}
