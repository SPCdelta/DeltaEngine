#include "Bow.hpp"

Bow::Bow(BehaviourScript* user) 
	: Weapon(user) 
{

}

void Bow::Use()
{
	std::shared_ptr<GameObject> arrow = _user->gameObject->Instantiate();
	arrow->transform->position.Set(_user->transform->position);
	arrow->AddComponent<Projectile>()->SetProjectileData(
	{
		"arrow", 
		8, 
		5.0f, 
		GetAimDirection()
	});
}