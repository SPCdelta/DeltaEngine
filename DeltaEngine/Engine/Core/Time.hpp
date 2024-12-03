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

	friend class Application;

private:
	static Time instance;
	static float deltaTime;
	static void SetDeltaTime(float deltaTime);
	Time() {}
};