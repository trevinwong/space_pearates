#include "operate_tower_event.hpp"

OperateTowerEvent::OperateTowerEvent(glm::vec2 _position, BUILD_TOWER_UI_BUTTON_TYPE _operationType, EntityManager& _entityManager):
  position(_position), operationType(_operationType), entityManager(_entityManager)
{
}

OperateTowerEvent::~OperateTowerEvent()
{
}

glm::vec2 OperateTowerEvent::getPosition()
{
  return this->position;
}

BUILD_TOWER_UI_BUTTON_TYPE OperateTowerEvent::getOperationType()
{
  return this->operationType;
}

EntityManager& OperateTowerEvent::getEntityManager()
{
  return this->entityManager;
}
