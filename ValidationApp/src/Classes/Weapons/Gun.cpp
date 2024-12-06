#include "Gun.hpp"

void Gun::Use() 
{
	std::shared_ptr<GameObject> bullet = _user->gameObject->Instantiate();
	bullet->transform->position.Set(_user->transform->position);
	bullet->transform->scale.Set({ 0.5f, 0.5f });
	bullet->AddComponent<Projectile>()->SetProjectileData({ "bullet", 20, 5.0f, GetAimDirection() });
}
