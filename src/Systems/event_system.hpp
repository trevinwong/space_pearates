#ifndef SPRITE_SYSTEM_H
#define SPRITE_SYSTEM_H

#include "utility.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "entity.hpp"
#include "sprite_component.hpp"
#include "transform_component.hpp"
#include "color_component.hpp"

/* A subscriber can subscribe itself to a given observable (event).
 * When events come into the event queue, the EventSystem alerts all
 * observers who are subscribed to that type of observable.
 */

// Each event is the observable. Each system is the observer.

class EventSystem
{
public:
	void processEvent(Event event);

	template <typename T>
	void subscribe(Subscriber &subscriber);
	{
		subscribers[T::eventName].push_back(subscriber);
	}
	unordered_map<string, vector<Subscriber>> subscribers;
};

#endif


