#pragma once

#include <iostream>
#include <thread>

#include <Engine/Core/Time.hpp>

#include "../Item.hpp"
#include "../../Player.hpp"

enum class PotionType
{
	AttackUp,
	Defense,
	Healing,
	Speed,
	None
};

class Potion : public Item
{
   public:
	Potion(float time, float value, std::string name): _time{time}, _value{value}, Item(name) {}

	virtual void Use(Player& player) = 0;
	virtual void Update() {}

	virtual PotionType GetType() { return PotionType::None; }

   protected:
	float _time;
	float _value;
	
   public:
	float GetTime() const { return _time; }
	float GetValue() const { return _value; }
};
