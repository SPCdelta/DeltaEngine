#include "WeaponTypeUtils.hpp"

const std::unordered_map<WeaponType, std::string> WeaponTypeUtils::_weaponTypes = {
		{WeaponType::Gun, "gun"},
		{WeaponType::Bow, "bow"},
		{WeaponType::Boomerang, "boomerang"}
};

const std::string WeaponTypeUtils::ToString(WeaponType type)
{
	auto it = _weaponTypes.find(type);
	if (it != _weaponTypes.end())
	{
		return it->second;
	}
	throw std::invalid_argument("Unknown WeaponType");
}

WeaponType WeaponTypeUtils::FromString(const std::string& type)
{
	for (const auto& pair : _weaponTypes)
	{
		if (pair.second == type)
		{
			return pair.first;
		}
	}
	throw std::invalid_argument("Unknown WeaponType string: " + type);
}
