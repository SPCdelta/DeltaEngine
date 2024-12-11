#include "Time.hpp"

Time Time::instance;
float Time::deltaTime = 0.0f;
float Time::multiplier = 1.f;

float Time::GetDeltaTime()
{
	return instance.deltaTime * multiplier;
}

float Time::GetMultiplier()
{
	return multiplier;
}

void Time::SetDeltaTime(float deltaTime)
{
	instance.deltaTime = deltaTime;
}

void Time::IncreaseMultiplier(float multiplier)
{
	float newMultiplier = instance.multiplier + multiplier;
	instance.multiplier = newMultiplier > 0 ? newMultiplier : 0.1f;
}
