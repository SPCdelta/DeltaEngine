#pragma once
#include "Potion.hpp"
class SpeedPotion : public Potion
{
   public:
	SpeedPotion(float time, float value) : Potion(time, value) {}
	void Use();
};
