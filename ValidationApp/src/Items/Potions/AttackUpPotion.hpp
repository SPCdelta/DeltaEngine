#pragma once

#include "Potion.hpp"

class AttackUpPotion : public Potion
{
   private:
	bool IsActive = false;
	float _elapsedTime = 0.0f;
	float _potionDuration = 0.0f;
	Player* _affectedPlayer = nullptr;
	float _originalDamage  = 0.0f;

   public:
	AttackUpPotion(float time, float value, std::string name, std::string sprite) : Potion(time, value, name, sprite){}

	void Use(Player& player) override;
	void Update() override;

	PotionType GetType() override { return PotionType::AttackUp; }
};
  