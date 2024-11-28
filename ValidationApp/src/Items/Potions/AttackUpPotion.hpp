#pragma once
#include "Potion.hpp"
class AttackUpPotion : public Potion
{
   public:
	AttackUpPotion(float time, float value, std::string name, Player player) : Potion(time, value, name, player){}
	void Use();
};
  