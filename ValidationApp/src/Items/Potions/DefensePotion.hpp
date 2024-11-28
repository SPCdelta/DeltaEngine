#pragma once
#include "Potion.hpp"
class DefensePotion : public Potion
{
   public:
	DefensePotion(float time, float value, std::string name) : Potion(time, value, name) {}
	void Use(Player player);
};
