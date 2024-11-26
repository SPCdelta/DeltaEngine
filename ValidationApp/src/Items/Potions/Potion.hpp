#pragma once
#include <thread>
#include <chrono>
class Potion
{
   public:
	Potion(float time, float value) : time(time), value(value) {}
	virtual void Use();
   protected:
	float time;
	float value;
};
