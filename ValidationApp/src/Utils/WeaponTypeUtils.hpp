#pragma once

#include "Engine/Delta.hpp"
#include "../Classes/Weapons/WeaponType.hpp"

class WeaponTypeUtils
{
public:
	static const std::string ToString(WeaponType type);
	static WeaponType FromString(const std::string& type);
private:
	static const std::unordered_map<WeaponType, std::string> _weaponTypes;
};

