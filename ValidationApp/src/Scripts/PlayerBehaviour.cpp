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

	rigidbody->onCollisionEnter.Register(
		[this](Collider& collider)
		{

		}
	);

	rigidbody->onCollisionExit.Register(
		[this](Collider& collider)
		{ 

		}
	);
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
