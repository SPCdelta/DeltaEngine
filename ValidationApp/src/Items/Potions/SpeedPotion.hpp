#pragma once

#include "Potion.hpp"

class SpeedPotion : public Potion
{
private:
	bool IsActive = false;
	float _elapsedTime = 0.0f;
	float _potionDuration = 0.0f;

	Player* _affectedPlayer = nullptr;
	float _originalSpeed = 0;

	PotionType GetPotionType() const override;

public:
	SpeedPotion(float time, float value, std::string name, std::string sprite);

	void Use(Player& player);
	bool Update() override;

	std::unique_ptr<Item> Clone() const override;
};
