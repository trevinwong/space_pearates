#include "timer.hpp"

Timer::Timer()
{
}

Timer::Timer(float _maxTime, float _elapsedTime) :
	maxTime(_maxTime), elapsedTime(_elapsedTime)
{
}

float Timer::getParameterLinear()
{
  return elapsedTime / maxTime;
}

float Timer::getParameterQuadratic()
{
  float t = elapsedTime / maxTime;
  return t * t;
}

void Timer::update(float dt)
{
	elapsedTime += dt;
}

float Timer::getTimeLeft()
{
	return maxTime - elapsedTime;
}

void Timer::reset() 
{
	elapsedTime = 0;
}
