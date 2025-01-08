#pragma once

#include "Weapon.hpp"
#include "../Projectiles/Projectile.hpp"

class Gun : public Weapon
{
public:
	Gun(BehaviourScript* user) : Weapon(user) { }

	void Use() override
	{
		std::shared_ptr<GameObject> bullet = _user->transform->gameObject->Instantiate();
		bullet->transform->position.Set(_user->transform->position);
		bullet->transform->scale.Set({0.5f, 0.5f});
		bullet->AddComponent<Projectile>()->SetProjectileData({"bullet", 15, 5.0f, GetAimDirection()});
	}
};