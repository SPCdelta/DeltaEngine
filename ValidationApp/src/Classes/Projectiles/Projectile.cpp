#include "Projectile.hpp"

void Projectile::OnStart() 
{
	gameObject->AddComponent<Despawner>(DEFAULT_PROJECTILE_DESPAWN_TIME);
	gameObject->AddComponent<CircleCollider>()->SetTrigger(true);
	rigidbody = gameObject->AddComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
}

void Projectile::OnUpdate()
{
	
}