#include "event_system.hpp"

EventSystem::EventSystem()
{

}

EventSystem::process()
{

}

EventSystem::addEvent(Observable observable, bool processNow)
{
	observables.push_back(observable);
	if (processNow) {
			
	}
}

// Given a type of Observable, subscribe to all observables of that type
// that come in
EventSystem::subscribe(Observable observable, Observer &observer)
{
	observers[observable.typeID].push_back(observer);
}
