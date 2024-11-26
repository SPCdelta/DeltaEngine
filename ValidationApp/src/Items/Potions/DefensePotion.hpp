#pragma once
#include "Potion.hpp"
class DefensePotion : public Potion
{
   public:
	DefensePotion(float time, float value);
	void Use();
};
