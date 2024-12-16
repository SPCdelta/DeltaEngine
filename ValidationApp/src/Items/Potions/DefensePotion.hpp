#pragma once

#include "Potion.hpp"

class DefensePotion : public Potion
{
   private:
	bool IsActive = false;
	float _elapsedTime = 0.0f;
	float _potionDuration = 0.0f;
	Player* _affectedPlayer = nullptr;
	int _originalShield = 0;

   public:
	DefensePotion(float time, float value, std::string name, std::string sprite) : Potion(time, value, name, sprite) {}

	void Use(Player& player) override;
	bool Update() override;
	Item* Clone() const override;
	PotionType GetType() override { return PotionType::Defense; }
};
