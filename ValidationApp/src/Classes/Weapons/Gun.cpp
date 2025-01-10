#include "Gun.hpp"

Gun::Gun(BehaviourScript* user) : Weapon{user}
{
}

void Gun::Use()
{
	std::shared_ptr<GameObject> bullet = _user->gameObject->Instantiate();
	bullet->transform->position.Set(_user->transform->position);
	bullet->transform->scale.Set({ 0.5f, 0.5f });
	bullet->AddComponent<Projectile>()->SetProjectileData({ "bullet", 15, 5.0f, GetAimDirection() });
}

WeaponType Gun::GetWeaponType() const
{
	return WeaponType::Gun;
}
