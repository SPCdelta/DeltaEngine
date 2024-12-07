#pragma once

#include "Engine/Delta.hpp"

#include "Potion.hpp"
#include "SpeedPotion.hpp"
#include "DefensePotion.hpp"
#include "HealingPotion.hpp"
#include "AttackUpPotion.hpp"

class PotionFactory
{
   public:
	static std::unique_ptr<Potion> CreatePotion(PotionType type, const Json::json& data)
	{
		switch (type)
		{
			case PotionType::AttackUp:
				return std::make_unique<AttackUpPotion>(data["time"], data["value"], data["name"], data["sprite"]);
			case PotionType::Defense:
				return std::make_unique<DefensePotion>(data["time"], data["value"], data["name"], data["sprite"]);
			case PotionType::Healing:
				return std::make_unique<HealingPotion>(data["time"], data["value"], data["name"], data["sprite"]);
			case PotionType::Speed:
				return std::make_unique<SpeedPotion>(data["time"], data["value"], data["name"], data["sprite"]);
			default:
				throw std::invalid_argument("Unknown PotionType");
		}
	}
};
