#include "Time.hpp"

Time Time::instance;
float Time::deltaTime = 0.0f;

float Time::GetDeltaTime()
{
	return instance.deltaTime;
}

void Time::SetDeltaTime(float deltaTime)
{
	instance.deltaTime = deltaTime;
}
