#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include "Events/event.hpp"

class Subscriber {
public:
  virtual void processEvent(Event *event) = 0;
};

#endif
