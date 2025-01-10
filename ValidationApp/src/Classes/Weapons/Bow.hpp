#pragma once

#include "../Projectiles/Projectile.hpp"
#include "Weapon.hpp"

class Bow : public Weapon
{
public:
	Bow(BehaviourScript* user);

	void Use() override;
	void Update(float deltaTime) override;
	WeaponType GetWeaponType() const override;
};