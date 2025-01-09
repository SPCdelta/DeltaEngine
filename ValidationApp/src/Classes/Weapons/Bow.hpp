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
		arrow->AddComponent<CircleCollider>()->SetTrigger(true);
		arrow->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
		arrow->AddComponent<Lifetime>(2.0f);
		arrow->transform->position.Set(_user->transform->position);
		arrow->AddComponent<Projectile>()->SetProjectileData({"arrow", 8, 5.0f, GetAimDirection()});
	}
};