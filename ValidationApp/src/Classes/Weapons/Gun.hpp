#pragma once

#include "Weapon.hpp"
#include "../Projectiles/Projectile.hpp"

class Gun : public Weapon
{
public:
	Gun(BehaviourScript* user);

	void Use() override;
	WeaponType GetWeaponType() const override;
};