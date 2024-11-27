#pragma once
#include <iostream>
#include <thread>
#include <chrono>
class Potion
{
   public:
	Potion(float time, float value) : _time{time}, _value{value} {}
	virtual void Use() = 0;
   protected:
	float _time;
	float _value;
};
