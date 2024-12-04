#pragma once

#include "Engine/Delta.hpp"

#include "../Classes/DamageBehaviour.hpp"
#include "../Classes/FloorBehaviour.hpp"
#include "../Classes/PlayerInput.hpp"
#include "Boomerang.hpp"

class PlayerBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	~PlayerBehaviour()
	{
		sprite = nullptr;
		rigidbody = nullptr;
		_sfx = nullptr;

		delete _floorBehaviour;
		delete _damageBehaviour;
	}

	void ThrowBoomerang();

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

	void UpdateAttack(float deltaTime);

private:
	FloorBehaviour* _floorBehaviour{nullptr};
	DamageBehaviour* _damageBehaviour{nullptr};
	PlayerInput _playerInput{ this };

	// Weapons
	Boomerang* _boomerang = nullptr;

	// Audio
	Audio::SFXSource* _sfx;

	Math::Vector2 _moveDirection{ 0.0f, 0.0f };
	int _mouseX = 0;
	int _mouseY = 0;

	float _moveSpeed = 6.0f;
	float _iceAcceleration = 2.0f;

	FloorType _onFloor{ FloorType::NORMAL };

	bool _attacking{false};
	float _attackTime{0.0f};
	const float _attackDuration = 0.4f;	
	void StartAttack() { _attackTime = _attackDuration; }

	int hp{20};

	float deathElapsedTime = 0.0f;
	bool deathSoundPlayed = false;
};