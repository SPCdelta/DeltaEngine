#pragma once

#include <Engine/Delta.hpp>

#include "../Classes/Projectiles/Projectile.hpp"

class BoomerangBehaviour : public Projectile
{
public:
	void OnStart() override;
	void OnUpdate() override;

	void Throw(std::shared_ptr<GameObject> thrower, float speed, Math::Vector2 origin, Math::Vector2 direction);
	void Return();

	Events::EventDispatcher<Events::Event> onFinish{};

private:
	std::shared_ptr<GameObject> _thrower;
	Audio::SFXSource* audioSource = nullptr;

	// State
	bool _isReturning = false; 
	bool _finished = false;

	// Animation
	float _rotationsPerSecond = 3.0f;

	// Variables
	float _distance = 10.0f;
	float _throwSpeed = 0.0f;
	Vector2 _originPosition{};
	Vector2 _targetPosition{};
};