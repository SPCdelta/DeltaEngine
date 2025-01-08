#include "DummyBehaviour.hpp"

void DummyBehaviour::OnStart()
{ 
	gameObject->AddComponent<Sprite>("player")->SetLayer(Layer::Player);
	gameObject->AddComponent<BoxCollider>();
	Rigidbody* rigidbody = gameObject->AddComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);

	rigidbody->onTriggerEnter.Register
	(
		[this](Collider& collider)
		{
			if (collider.transform.gameObject->GetTag() == "projectile")
				const ProjectileData& projectileData = collider.transform.gameObject->GetComponent<Projectile>().GetProjectileData();
		}
	);
}

void DummyBehaviour::OnUpdate() 
{

}