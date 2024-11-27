#pragma once

#include <Engine/Delta.hpp>

class Boomerang : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	void Throw(GameObject* thrower, float speed, Math::Vector2 origin, Math::Vector2 direction);

private:
	GameObject* _thrower = nullptr;
	Rigidbody* rigidbody = nullptr;
};