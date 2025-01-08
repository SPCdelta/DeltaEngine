#pragma once

#include "Engine/Delta.hpp"

class PhysicsBehaviour : public BehaviourScript
{
public:
	// Components
	Physics::Rigidbody* rigidbody = nullptr;

	// Methods
	void OnStart() override;
	void OnUpdate() override;
};