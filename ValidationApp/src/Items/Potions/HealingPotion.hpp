#pragma once
#include "Potion.hpp"
class HealingPotion : public Potion
{
   public:
	HealingPotion(float time, float value);
	void Use();
};
