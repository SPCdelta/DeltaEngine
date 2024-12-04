#pragma once

#include <Engine/Delta.hpp>

class Boomerang : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	void Throw(GameObject* thrower, float speed, Math::Vector2 origin, Math::Vector2 direction);
	void Return();

	Events::EventDispatcher<Events::Event> onFinish{};

private:
	GameObject* _thrower = nullptr;
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;
	Audio::SFXSource* audioSource = nullptr;

	float _distance = 10.0f;
	float _rotationsPerSecond = 3.0f;

	float _throwSpeed = 0.0f;
	Vector2 _targetPosition{};
	bool _isReturning = false; 
	bool _finished = false;
};