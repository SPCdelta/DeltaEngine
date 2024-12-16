#pragma once

#include "Potion.hpp"

class HealingPotion : public Potion
{
   public:
	HealingPotion(float time, float value, std::string name, std::string sprite) : Potion(time, value, name, sprite) {}

	void Use(Player& player) override;
	Item* Clone() const override;
	PotionType GetType() override { return PotionType::Healing; }
};
