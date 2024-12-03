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

	void ThrowBoomerang();

	// Components
	Sprite* sprite = nullptr;
	Rigidbody* rigidbody = nullptr;

private:
	FloorBehaviour* _floorBehaviour{nullptr};
	DamageBehaviour* _damageBehaviour{nullptr};
	PlayerInput _playerInput{ this };

	Math::Vector2 _moveDirection{ 0.0f, 0.0f };
	int _mouseX = 0;
	int _mouseY = 0;

	float _moveSpeed = 6.0f;
	float _iceAcceleration = 2.0f;

	FloorType _onFloor{ FloorType::NORMAL };

	// TODO iframes
	//float _currentFrame{0.0f};
	//float _lastFrame{0.0f};

	//float GetDeltaTime()
	//{
	//	_currentFrame = Rendering::GetTicks() / 1000.f;	 // TODO magic num
	//	float deltaTime = _currentFrame - _lastFrame;
	//	_lastFrame = _currentFrame;

	//	return deltaTime;
	//}
};