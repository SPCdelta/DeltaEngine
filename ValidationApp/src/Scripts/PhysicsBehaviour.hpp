#pragma once

#include <iostream>
#include "../GameObject.hpp"
#include "../BehaviourScript.hpp"
#include "../Physics/Rigidbody.hpp"

class PhysicsBehaviour : public BehaviourScript
{
   public:
	// Components
	Physics::Rigidbody* rigidbody = nullptr;

	// Methods
	void OnStart() override 
	{ 
		rigidbody = &gameObject->GetComponent<Physics::Rigidbody>();
	}

	void OnUpdate() override
	{

	}
};