#ifndef OPERATE_TOWER_EVENT_H
#define OPERATE_TOWER_EVENT_H

#include "event.hpp"
#include "../utility.hpp"
#include "../entity.hpp"
#include "../entity_manager.hpp"

/*
  - Build Event
  - Sell Event
  - Upgrade Evnet
  - etc.
*/
class OperateTowerEvent : public Event 
{
public:
  OperateTowerEvent(glm::vec2 position, BUILD_TOWER_UI_BUTTON_TYPE operation, EntityManager& entityManager);
  ~OperateTowerEvent();

  glm::vec2 getPosition();
  BUILD_TOWER_UI_BUTTON_TYPE getOperationType();
  EntityManager& getEntityManager();

  static const int typeId = EventType::operate_tower;
  inline virtual int getTypeId() const { return typeId; };
private:
  glm::vec2 position;
  BUILD_TOWER_UI_BUTTON_TYPE operationType;
  EntityManager& entityManager;
};

#endif // !OPERATE_TOWER_EVENT_H
