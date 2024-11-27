#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);

	// Events
	rigidbody->onTriggerEnter.Register(
		[this](Collider& collider)
		{ 
			const std::string& tag{collider.transform.gameObject->GetTag()};
			if (tag == "ice")
			{
				_iceCount++;
			}
			else if (tag == "mud")
			{
				_mudCount++;
			}
		}
	);

	rigidbody->onTriggerExit.Register(
		[this](Collider& collider)
		{ 
			const std::string& tag{collider.transform.gameObject->GetTag()};
			if (tag == "ice")
			{
				_iceCount--;
			}
			else if (tag == "mud")
			{
				_mudCount--;
			}
		}
	);

	// Input
	InputManager::activateCategory("Gameplay");
	InputManager::onKeyPressed(KEY_W, [this](Input& e) { _moveDirection.SetY(1.0f); }, "Gameplay");
	InputManager::onKeyPressed(KEY_S, [this](Input& e) { _moveDirection.SetY(-1.0f); }, "Gameplay");
	InputManager::onKeyPressed(KEY_A, [this](Input& e) { _moveDirection.SetX(-1.0f); }, "Gameplay");
	InputManager::onKeyPressed(KEY_D, [this](Input& e) { _moveDirection.SetX(1.0f); }, "Gameplay");

	InputManager::onKeyReleased(KEY_W, [this](Input& e) { _moveDirection.SetY(0.0f); }, "Gameplay");
	InputManager::onKeyReleased(KEY_S, [this](Input& e) { _moveDirection.SetY(0.0f); }, "Gameplay");
	InputManager::onKeyReleased(KEY_A, [this](Input& e) { _moveDirection.SetX(0.0f); }, "Gameplay");
	InputManager::onKeyReleased(KEY_D, [this](Input& e) { _moveDirection.SetX(0.0f); }, "Gameplay");
}

void PlayerBehaviour::OnUpdate() 
{
	// Order is important here
	if (_mudCount > 0)
	{
		_onFloor = FloorType::MUD;
	}
	else if (_iceCount > 0)
	{
		_onFloor = FloorType::ICE;
	}
	else
	{
		_onFloor = FloorType::NORMAL;
	}

	Math::Vector2 currentVelocity{ rigidbody->GetVelocity() };
	if (_moveDirection != Math::Vector2{0.0f, 0.0f})
	{
		switch (_onFloor)
		{
			case FloorType::NORMAL:
				{
					rigidbody->SetVelocity(_moveDirection * _moveSpeed);
				}
				break;

			case FloorType::ICE:
				if (rigidbody->GetSpeed() < _moveSpeed)
				{
					rigidbody->AddForce(_moveDirection * _moveSpeed, ForceMode::ACCELERATE);
				}

				Math::Vector2 currentVelocity{rigidbody->GetVelocity()};
				rigidbody->AddForce(-currentVelocity * 1.0f, ForceMode::ACCELERATE);
				if (rigidbody->GetSpeed() <= 0.0f)
				{
					rigidbody->SetVelocity(Math::Vector2(0.0f, 0.0f));
				}
				break;

			case FloorType::MUD:
				{
					rigidbody->SetVelocity(_moveDirection * (_moveSpeed * 0.5f));
				}
				break;
		}
	}
	else
	{
		switch (_onFloor)
		{
			case FloorType::NORMAL:
				rigidbody->AddForce(-currentVelocity * 10.0f,
									ForceMode::ACCELERATE);
				break;
			case FloorType::ICE:
				rigidbody->AddForce(-currentVelocity * 1.0f,
									ForceMode::ACCELERATE);
				break;
			case FloorType::MUD:
				rigidbody->SetVelocity({0.0f, 0.0f});
				break;
		}
	}
}
