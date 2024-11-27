#pragma once

#include "Engine/Delta.hpp"

class WalkBehaviour : public BehaviourScript
{
	public:
		void OnStart() override
		{
			Sprite& sprite = gameObject->GetComponent<Sprite>();
			rigidbody = &gameObject->GetComponent<Rigidbody>();
			rigidbody->SetGravityScale(0.0f);

			// Events
			rigidbody->onTriggerExit.Register([this](Collider& collider) { _sensorCount--; });
			rigidbody->onTriggerEnter.Register([this](Collider& collider) { _sensorCount++; });

			// Input
			InputManager::activateCategory("Gameplay");

			// Check if the sprite has an animator, and call Play
			InputManager::keyPressed(KEY_W, [this, sprite](Input& e) 
			{ 
				_moveDirection.SetY(0.25f); 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(sprite.GetSheet(), Direction::UP);
			}, "Gameplay");
			InputManager::keyPressed(KEY_S, [this, sprite](Input& e) 
			{ 
				_moveDirection.SetY(-0.25f); 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(sprite.GetSheet(), Direction::DOWN); 
			}, "Gameplay");
			InputManager::keyPressed(KEY_A, [this, sprite](Input& e) 
			{ 
				_moveDirection.SetX(-0.25f); 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(sprite.GetSheet(), Direction::LEFT); 
			}, "Gameplay");
			InputManager::keyPressed(KEY_D, [this, sprite](Input& e) 
			{ 
				_moveDirection.SetX(0.25f); 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(sprite.GetSheet(), Direction::RIGHT); 
			}, "Gameplay");

			InputManager::onKeyReleased(KEY_W, [this, sprite](Input& e) 
			{ 
				_moveDirection.SetY(0.0f); 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(sprite.GetSheet(), Direction::NONE); 
			}, "Gameplay");
			InputManager::onKeyReleased(KEY_S, [this, sprite](Input& e) 
			{ 
				_moveDirection.SetY(0.0f); 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(sprite.GetSheet(), Direction::NONE); 
			}, "Gameplay");
			InputManager::onKeyReleased(KEY_A, [this, sprite](Input& e) 
			{ 
				_moveDirection.SetX(0.0f); 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(sprite.GetSheet(), Direction::NONE); 
			}, "Gameplay");
			InputManager::onKeyReleased(KEY_D, [this, sprite](Input& e) 
			{ 
				_moveDirection.SetX(0.0f); 
				if (sprite.GetAnimator()) sprite.GetAnimator()->Play(sprite.GetSheet(), Direction::NONE); 
			}, "Gameplay");
		}

		void OnUpdate() override
		{
			Math::Vector2 currentVelocity{rigidbody->GetVelocity()};
			if (_moveDirection != Math::Vector2{0.0f, 0.0f})
			{
				rigidbody->SetVelocity(_moveDirection * _moveSpeed);
			}
		}

	private:
		int test{0};
		Rigidbody* rigidbody{nullptr};
		Math::Vector2 _moveDirection{0.0f, 0.0f};
		float _moveSpeed = 6.0f;
		int _sensorCount = 0;
};