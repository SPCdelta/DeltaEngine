#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);

	// Events
	rigidbody->onTriggerExit.Register(
		[this](Collider& collider)
		{ 
			_sensorCount--;
		}
	);

	rigidbody->onTriggerEnter.Register(
		[this](Collider& collider)
		{ 
			_sensorCount++;
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

	// Bij het testen van inventory, Dit aanzetten! 
	
	//InputManager::onKeyPressed(
	//	KEY_V, [this](Input& e) { inventory.AddItem(_item1, 4); }, "Gameplay");
	//InputManager::onKeyPressed(
	//	KEY_E, [this](Input& e) { inventory.PrintInventory(); }, "Gameplay");
	//InputManager::onKeyPressed(
	//	KEY_Q, [this](Input& e) { inventory.RemoveItem(_item1, 5);}, "Gameplay");
}

void PlayerBehaviour::OnUpdate() 
{
	if (_sensorCount == 0) _onFloor = FloorType::NORMAL;
	else _onFloor = FloorType::ICE;

	Math::Vector2 currentVelocity{ rigidbody->GetVelocity() };
	if (_moveDirection != Math::Vector2{0.0f, 0.0f})
	{
		switch (_onFloor)
		{
			case FloorType::NORMAL:
				rigidbody->SetVelocity(_moveDirection * _moveSpeed);
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
				rigidbody->SetVelocity(_moveDirection * (_moveSpeed * 0.75f));
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
