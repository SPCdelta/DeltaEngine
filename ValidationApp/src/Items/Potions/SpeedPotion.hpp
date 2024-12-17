#pragma once

#include "Potion.hpp"

class SpeedPotion : public Potion
{
   private:
	bool IsActive = false;
	float _elapsedTime = 0.0f;
	float _potionDuration = 0.0f;
	Player* _affectedPlayer = nullptr;
	float _originalSpeed = 0.0f;

   public:
	SpeedPotion(float time, float value, std::string name, std::string sprite) : Potion(time, value, name, sprite) {}

	void Use(Player& player) override;
	void Update() override;

	PotionType GetType() override { return PotionType::Speed; }
};
