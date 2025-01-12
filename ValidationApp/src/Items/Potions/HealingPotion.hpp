#pragma once

#include "Potion.hpp"

#include "Engine/Delta.hpp"

class HealingPotion : public Potion
{
public:
	HealingPotion(float time, float value, std::string name, std::string sprite);

	void Use(Player& player) override;

	std::unique_ptr<Item> Clone() const override;

	PotionType GetPotionType() const override;
};
