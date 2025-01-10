#pragma once

#include "Engine/Delta.hpp"

#include "Weapon.hpp"
#include "../../Scripts/BoomerangBehaviour.hpp"

class Boomerang : public Weapon
{
public:
	Boomerang(BehaviourScript* user);

	void Use() override;
	WeaponType GetWeaponType() const override;
private:
	BoomerangBehaviour* _boomerang;
};

