#ifndef EVENT_H
#define EVENT_H

namespace EventType {
  enum EventType {
    collision,
    max_count
  };
}

class Event
{
public:
  virtual int getTypeId() const = 0;
};

#endif
