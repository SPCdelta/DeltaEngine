#pragma once

#include "Engine/Delta.hpp"

class PhysicsBehaviour : public BehaviourScript
{
public:
	// Components
	Physics::Rigidbody* rigidbody = nullptr;

	// Methods
	void OnStart() override
	{
		rigidbody = &transform->gameObject->GetComponent<Physics::Rigidbody>();
		rigidbody->onTriggerEnter.Register(
			[this](Collider& collider) 
			{
				std::cout << "OnTriggerEnter" << std::endl;
			});

		rigidbody->onTriggerExit.Register(
			[this](Collider& collider)
			{
				std::cout << "OnTriggerExit" << std::endl;
			});

		rigidbody->onCollisionEnter.Register(
			[this](Collider& collider) 
			{
				std::cout << "OnCollisionEnter" << std::endl;
				rigidbody->AddForce(Math::Vector2::up * 10.0f, ForceMode::IMPULSE);
			});

		rigidbody->onCollisionExit.Register(
			[this](Collider& collider) 
			{
				std::cout << "OnCollisionExit" << std::endl;
			});
	}

	void OnUpdate() override
	{

	}
};