#pragma once

#include "Engine/Delta.hpp"

#include "../Classes/FloorBehaviour.hpp"
#include "../Classes/PlayerInput.hpp"

class PlayerBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

private:
	FloorBehaviour* _floorBehaviour = nullptr;
	PlayerInput _playerInput{ this };

	Math::Vector2 _moveDirection{ 0.0f, 0.0f };

	float _moveSpeed = 6.0f;
	float _iceAcceleration = 2.0f;

	FloorType _onFloor{ FloorType::NORMAL };
};