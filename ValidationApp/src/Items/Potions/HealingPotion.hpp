#pragma once
#include "Potion.hpp"
class HealingPotion : public Potion
{
   public:
	HealingPotion(float time, float value, std::string name, Player player) : Potion(time, value, name, player) {}
	void Use();
};
