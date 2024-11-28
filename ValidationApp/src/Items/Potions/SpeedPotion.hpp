#pragma once
#include "Potion.hpp"
class SpeedPotion : public Potion
{
   public:
	SpeedPotion(float time, float value, std::string name, Player player) : Potion(time, value, name, player) {}
	void Use();
};
