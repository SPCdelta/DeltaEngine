#pragma once
#include "Potion.hpp"
class AttackUpPotion : public Potion
{
   private:
	bool IsActive = false;
	float _elapsedTime = 0.0f;
	float _potionDuration = 0.0f;
	Player* _affectedPlayer = nullptr;
	int _originalDamage  = 0;
   public:
	AttackUpPotion(float time, float value, std::string name) : Potion(time, value, name){}
	void Use(Player& player);
	void Update();
};
  