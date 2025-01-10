#include "Bow.hpp"

Bow::Bow(BehaviourScript* user) : Weapon{user}
{
}

void Bow::Use()
{
    if (_timeSinceLastAttack >= _attackCooldown)
    {
        _timeSinceLastAttack = 0.0f;

        std::shared_ptr<GameObject> arrow = _user->transform->gameObject->Instantiate();
		arrow->AddComponent<CircleCollider>()->SetTrigger(true);
		arrow->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
		arrow->AddComponent<Lifetime>(DEFAULT_LIFETIME);
		arrow->transform->position.Set(_user->transform->position);
		arrow->AddComponent<Projectile>()->SetProjectileData({"arrow", 8, 5.0f, GetAimDirection()});
    }
}

void Bow::Update(float deltaTime)
{
	_timeSinceLastAttack += deltaTime;
}

WeaponType Bow::GetWeaponType() const
{
	return WeaponType::Bow;
}
