#include "PotionTypeUtils.hpp"

const std::unordered_map<PotionType, std::string> PotionTypeUtils::_potionTypes =  {
		{PotionType::Healing, "healing"},
		{PotionType::Speed, "speed"},
		{PotionType::AttackUp, "attackup"},
		{PotionType::Defense, "defense"}
};

const std::string PotionTypeUtils::ToString(PotionType type)
{
	auto it = _potionTypes.find(type);
	if (it != _potionTypes.end())
	{
		return it->second;
	}
	throw std::invalid_argument("Unknown PotionType");
}

PotionType PotionTypeUtils::FromString(const std::string& type)
{
	for (const auto& pair : _potionTypes)
	{
		if (pair.second == type)
		{
			return pair.first;
		}
	}
	throw std::invalid_argument("Unknown PotionType string: " + type);
}
