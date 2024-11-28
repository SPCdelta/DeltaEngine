#pragma once
#include "Potion.hpp"
class HealingPotion : public Potion
{
   public:
	HealingPotion(float time, float value, std::string name) : Potion(time, value, name) {}
	void Use(Player player);
};
