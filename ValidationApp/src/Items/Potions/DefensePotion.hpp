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

	PotionType GetPotionType() const override;

public:
	DefensePotion(float time, float value, std::string name, std::string sprite);

	void Use(Player& player) override;
	bool Update() override;

	std::unique_ptr<Item> Clone() const override;
};
