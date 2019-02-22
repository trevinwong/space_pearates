#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
	Timer(float _maxTime, float _elapsedTime = 0.0f);
	float update(float dt);
	float getTimeLeft();
	float elapsedTime;
	float maxTime;
};

#endif
