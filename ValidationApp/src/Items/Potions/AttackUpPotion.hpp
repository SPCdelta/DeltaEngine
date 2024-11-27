#pragma once
#include "Potion.hpp"
class AttackUpPotion : public Potion
{
   public:
	AttackUpPotion(float time, float value) : Potion(time, value){}
	void Use();
};
  