#pragma once

class Application;

class Time
{
public:
	Time(const Time&) = delete;
	Time(Time&&) = delete;
	Time& operator=(const Time&) = delete;
	Time& operator=(Time&&) = delete;
	static float GetDeltaTime();
	static float GetMultiplier();

	friend class Application;

private:
	static Time instance;
	static float deltaTime;
	static float multiplier;
	static void SetDeltaTime(float deltaTime);
	static void IncreaseMultiplier(float multiplier);
	Time() {}
};