#ifndef EVENT_H
#define EVENT_H

#include "utility.hpp"

class Event 
{
public:
	virtual string getTypeName() const = 0;
};

#endif
