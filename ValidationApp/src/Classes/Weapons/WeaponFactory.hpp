#pragma once

#include "Engine/Delta.hpp"
#include "Weapon.hpp"

class WeaponFactory
{
public:
	static std::unique_ptr<Weapon> CreateWeapon(const std::string& type, BehaviourScript* user);
};

