#pragma once
#include "Potion.hpp"
class SpeedPotion : public Potion
{
   public:
	SpeedPotion(float time, float value, std::string name) : Potion(time, value, name) {}
	void Use(Player player);
};
