#pragma once

#include "Weapon.hpp"
#include "../Projectiles/Projectile.hpp"

class Gun : public Weapon
{
public:
	Gun(BehaviourScript* user)
		: Weapon(user)
	{

	}

	void Use() override;

private:
	
};