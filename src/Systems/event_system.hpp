#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "utility.hpp"
#include "Events/event.hpp"
#include "Events/collision_event.hpp"
#include "subscriber.hpp"

/*
 * This system handles everything related to Events.
 *
 * How it works:
 * - Have your class (likely a System) inherit from Subscriber so it can subscribe to events that the EventSystem will publish.
 * - Subscribe your class to an Event by calling subscribe<ExampleEvent>(*this). Make sure that the type you pass in inherits from Event.
 * - To emit an event, create a pointer to an Event, and then call eventSystem.propagateEvent(myEvent).
 * - Your event will then be passed to every single System subscribing to that type of event - they will then handle it in their own processEvent().
 *
 * Q: How do I call eventSystem.propagateEvent(myEvent) when my System isn't aware of the EventSystem?
 * A: A global EventSystem is created in World. Pass the reference into your update/draw loop for your System.
 */

class EventSystem
{
public:
  void propagateEvent(Event *event);
  unordered_map<int, vector<Subscriber*>> subscribers;

  template <typename T>
  void subscribe(Subscriber *subscriber)
  {
    subscribers[T::typeId].push_back(subscriber);
  }
};

#endif


