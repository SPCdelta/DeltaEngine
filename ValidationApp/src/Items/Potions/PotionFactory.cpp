#include "PotionFactory.hpp"

#include "../../Utils/PotionTypeUtils.hpp"
#include "../Potions/SpeedPotion.hpp"
#include "../Potions/HealingPotion.hpp"
#include "../Potions/DefensePotion.hpp"
#include "../Potions/AttackUpPotion.hpp"
#include "../../Utils/ItemTypeUtils.hpp"

std::unique_ptr<Potion> PotionFactory::CreatePotion(const std::string& type, float time, const std::string& sprite, const std::string& name, float value)
{
	switch (PotionTypeUtils::FromString(ItemTypeUtils::GetBody(type)))
	{
		case PotionType::AttackUp:
			return std::make_unique<AttackUpPotion>(time, value, name, sprite);
		case PotionType::Defense:
			return std::make_unique<DefensePotion>(time, value, name, sprite);
		case PotionType::Healing:
			return std::make_unique<HealingPotion>(time, value, name, sprite);
		case PotionType::Speed:
			return std::make_unique<SpeedPotion>(time, value, name, sprite);
		default:
			throw std::invalid_argument("Could not create potion from data.");
	}
}

Json::json PotionFactory::ToJson(const Potion& potion)
{
	return Json::json 
	{
		{"time", potion.GetTime()},
		{"value", potion.GetValue()},
		{"name", potion.GetName()},
		{"sprite", potion.GetSprite()},
		{"type", potion.GetType()},
	};
}
