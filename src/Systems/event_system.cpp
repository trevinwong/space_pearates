#include "event_system.hpp"

void EventSystem::propagateEvent(Event *event)
{
	for (Subscriber &subscriber : subscribers[event->getTypeName()]) {
		subscriber.processEvent(event);
	}		
	delete event;
}
