#include "timer.hpp"

Timer::Timer(float _maxTime, float _elapsedTime) :
	maxTime(_maxTime), elapsedTime(_elapsedTime)
{
}

void Timer::update(float dt)
{
	elapsedTime += dt;
}

float Timer::getTimeLeft()
{
	return maxTime - elapsedTime;
}
