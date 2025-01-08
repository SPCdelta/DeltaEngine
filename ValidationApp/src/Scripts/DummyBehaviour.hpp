#pragma once

#include <Engine/Delta.hpp>
#include "../Classes/Projectiles/Projectile.hpp"

class DummyBehaviour : public BehaviourScript
{
public:
	void OnStart() override
	{ 
		transform->gameObject->AddComponent<Sprite>("player")->SetLayer(Layer::Player);
		transform->gameObject->AddComponent<BoxCollider>();
		Rigidbody* rigidbody = transform->gameObject->AddComponent<Rigidbody>();
		rigidbody->SetGravityScale(0.0f);

		rigidbody->onTriggerEnter.Register(
			[this](Collider& collider)
			{
				if (collider.transform.gameObject->GetTag() == "projectile")
				{
					const ProjectileData& projectileData = collider.transform.gameObject->GetComponent<Projectile>().GetProjectileData();
					std::cout << "Hit by: " << projectileData.sprite << " for " << projectileData.damage << " hp." << std::endl;
				}
			}
		);
	}

	void OnUpdate() override
	{

	}
};