#include "PlayerBehaviour.hpp"

void PlayerBehaviour::OnStart() 
{
	sprite = &gameObject->GetComponent<Sprite>();
	rigidbody = &gameObject->GetComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);
	_floorBehaviour = new FloorBehaviour(*rigidbody);

	InputManager::onKeyPressed(KEY_Z, [this](Input& e) { ThrowBoomerang(); }, "Gameplay");
	InputManager::onMouseMove(
		[this](Input& e) 
		{ 
			_mousePos.Set(e.mouseX, e.mouseY);
		}
	);
}

void PlayerBehaviour::OnUpdate() 
{
	_moveDirection = _playerInput.GetDirection();
	_onFloor = _floorBehaviour->GetOnFloor();

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

void PlayerBehaviour::ThrowBoomerang() 
{
	std::shared_ptr<GameObject> boomerangObj = gameObject->Instantiate();
	Boomerang* boomerang = boomerangObj->AddComponent<Boomerang>();

	Math::Vector2 direction{0.0f, 0.0f};
	boomerang->Throw(gameObject, 5.0f, direction);
}
