#include "event_system.hpp"

EventSystem::processEvent(Event event)
{
	for (Subscriber subscriber : subscribers[event.typeID]) {
		subscriber.processEvent(event);
	}		
}
