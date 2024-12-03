#pragma once
#include <iostream>
#include <thread>
#include <Engine/Core/Time.hpp>

#include "../Item.hpp"
#include "../../Player.hpp"
class Potion : public Item
{
   public:
	Potion(float time, float value, std::string name)
		: _time{time}, _value{value}, Item(name)
	{
	}
	virtual void Use(Player& player) = 0;
   protected:
	float _time;
	float _value;
};
