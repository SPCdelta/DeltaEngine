#pragma once
#include "Potion.hpp"
class DefensePotion : public Potion
{
   public:
	DefensePotion(float time, float value, std::string name, Player player) : Potion(time, value, name, player) {}
	void Use();
};
