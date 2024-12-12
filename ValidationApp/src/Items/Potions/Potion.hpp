#pragma once

#include <iostream>

#include "Engine/Delta.hpp"
#include "../ConsumableItem.hpp"
#include "../../Player.hpp"

enum class PotionType
{
	AttackUp,
	Defense,
	Healing,
	Speed,
	None
};

class Potion : public ConsumableItem
{
   public:
	Potion(float time, float value, const std::string& name, const std::string& spriteName);

	virtual void Use(Player& player) = 0;
	virtual bool Update() { return true; };

	virtual PotionType GetType() { return PotionType::None; }

   protected:
	float _time;
	float _value;
	
   public:
	float GetTime() const { return _time; }
	float GetValue() const { return _value; }
};
