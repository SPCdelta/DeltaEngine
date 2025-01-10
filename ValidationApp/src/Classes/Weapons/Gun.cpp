#include "Gun.hpp"

Gun::Gun(BehaviourScript* user) : Weapon{user}
{
	_attackCooldown = 0.3f;
}

void Gun::Use()
{
	if (_timeSinceLastAttack >= _attackCooldown)
	{
		_timeSinceLastAttack = 0.0f;

		std::shared_ptr<GameObject> bullet = _user->gameObject->Instantiate();
		bullet->transform->position.Set(_user->transform->position);
		bullet->transform->scale.Set({ 0.5f, 0.5f });
		bullet->AddComponent<Projectile>()->SetProjectileData({ "bullet", 15, 5.0f, GetAimDirection() });
	}
}

void Gun::Update(float deltaTime)
{
	_timeSinceLastAttack += deltaTime;
}

WeaponType Gun::GetWeaponType() const
{
	return WeaponType::Gun;
}
