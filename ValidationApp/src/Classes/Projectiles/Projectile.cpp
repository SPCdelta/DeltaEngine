#include "Projectile.hpp"

void Projectile::OnStart() 
{
	//gameObject->AddComponent<CircleCollider>()->SetTrigger(true);
	//rigidbody = gameObject->AddComponent<Rigidbody>();
	//rigidbody->SetGravityScale(0.0f);
}

void Projectile::OnUpdate()
{
	transform->position += { (1.0f * Time::GetDeltaTime()), 0.0f};
	if (_timeAlive <= 0.0f)
	{
		gameObject->Destroy(gameObject);
	}
	else
	{
		_timeAlive -= Time::GetDeltaTime();
	}
}