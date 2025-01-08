#include "Time.hpp"

#include <exception>

Time Time::instance;

float Time::deltaTime = 0.0f;
float Time::multiplier = 1.f;
float Time::increment = 0.25f;

Time::Time()
{

}

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

void Time::SetMultiplier(float value)
{
	if (value > 1 || value <= 0)
	{
		throw std::exception{ "Multiplier value cannot be greater than 1." };
	}
	instance.multiplier = value;
}

void Time::SetIncrement(float value)
{
	if (value <= 0)
	{
		throw std::exception{"Increment value cannot be equal or lower than 0."};
	}
	instance.increment = value;
}

void Time::IncreaseMultiplier()
{
	float newMultiplier = instance.multiplier + increment;
	instance.multiplier = newMultiplier > MAX_MULTIPLIER ? instance.multiplier : newMultiplier;
}

void Time::DecreaseMultiplier()
{
	float newMultiplier = instance.multiplier - increment;
	instance.multiplier = newMultiplier > 0 ? newMultiplier : instance.multiplier;
}
