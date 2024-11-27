#pragma once

#include "Engine/Delta.hpp"

enum class FloorType
{
	NORMAL = 0,
	ICE = 1,
	MUD = 2,
};

class PlayerBehaviour : public BehaviourScript
{
public:
	void OnStart() override;
	void OnUpdate() override;

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

private:
	Math::Vector2 _moveDirection{ 0.0f, 0.0f };
	float _moveSpeed = 6.0f;
	float _iceAcceleration = 2.0f;

	int _iceCount{0};
	int _mudCount{0};

	FloorType _onFloor{ FloorType::NORMAL };
};