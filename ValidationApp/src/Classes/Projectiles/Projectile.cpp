#include "Projectile.hpp"

void Projectile::OnStart() 
{
	transform->gameObject->AddComponent<CircleCollider>()->SetTrigger(true);
	rigidbody = transform->gameObject->AddComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	transform->gameObject->AddComponent<Lifetime>(DEFAULT_PROJECTILE_DESPAWN_TIME);
}

void Projectile::OnUpdate()
{

}