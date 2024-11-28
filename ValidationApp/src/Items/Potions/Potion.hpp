#pragma once
#include <iostream>
#include <thread>
#include <chrono>

#include "../Item.hpp"
#include "../../Player.hpp"
class Potion : public Item
{
   public:
	Potion(float time, float value, std::string name, Player player)
		: _time{time}, _value{value}, Item(name), _player{player}
	{
	}
	virtual void Use() = 0;
   protected:
	float _time;
	float _value;
	Player _player;
};
