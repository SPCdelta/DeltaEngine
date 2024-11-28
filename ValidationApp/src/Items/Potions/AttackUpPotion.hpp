#pragma once
#include "Potion.hpp"
class AttackUpPotion : public Potion
{
   public:
	AttackUpPotion(float time, float value, std::string name) : Potion(time, value, name){}
	void Use(Player player);
};
  