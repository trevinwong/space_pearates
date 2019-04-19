#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
  Timer();
	Timer(float _maxTime, float _elapsedTime = 0.0f);
	void update(float dt);
  float getParameterLinear();
  float getParameterQuadratic();
	float getTimeLeft();
	void reset();
	float elapsedTime;
	float maxTime;
};

#endif
