#include "Bow.hpp"

Bow::Bow(BehaviourScript* user) : Weapon{user}
{
}

void Bow::Use()
{
    if (_timeSinceLastAttack >= _attackCooldown)
    {
        _timeSinceLastAttack = 0.0f;

        std::shared_ptr<GameObject> arrow = _user->gameObject->Instantiate();
        arrow->transform->position.Set(_user->transform->position);
        arrow->AddComponent<Projectile>()->SetProjectileData({ "arrow", 8, 5.0f, GetAimDirection() });
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
