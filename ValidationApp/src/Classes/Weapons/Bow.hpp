#pragma once

#include "../Projectiles/Projectile.hpp"
#include "Weapon.hpp"

class Bow : public Weapon
{
public:
	Bow(BehaviourScript* user) : Weapon(user) { }

	void Use() override
	{
		std::shared_ptr<GameObject> arrow = _user->transform->gameObject->Instantiate();
		arrow->transform->position.Set(_user->transform->position);
		arrow->AddComponent<Projectile>()->SetProjectileData({"arrow", 8, 5.0f, GetAimDirection()});
	}
};