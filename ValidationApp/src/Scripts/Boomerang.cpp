#include "Boomerang.hpp"

void Boomerang::OnStart() 
{
	gameObject->AddComponent<Sprite>("player")->SetLayer(Layer::Projectiles);
	gameObject->AddComponent<BoxCollider>()->SetTrigger(true);
	rigidbody = gameObject->AddComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);

	rigidbody->onCollisionEnter.Register(
		[this](Collider& collider)
		{ 
			std::cout << "Meow Col!" << std::endl;
		}
	);

	rigidbody->onTriggerEnter.Register(
		[this](Collider& collider)
		{ 
			std::cout << "Meow Trig!" << std::endl;
		}
	);
}

void Boomerang::OnUpdate() 
{
	
}

void Boomerang::Throw(GameObject* thrower, float speed, Math::Vector2 origin, Math::Vector2 direction)
{
	_thrower = thrower;
	gameObject->transform->position.Set(origin);
	rigidbody->AddForce(direction * speed, ForceMode::IMPULSE);
}
