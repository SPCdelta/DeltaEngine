#include "Boomerang.hpp"

void Boomerang::OnStart() 
{
	gameObject->AddComponent<Sprite>("player")->SetLayer(Layer::Projectiles);
	gameObject->AddComponent<BoxCollider>()->SetTrigger(true);
	rigidbody = gameObject->AddComponent<Rigidbody>();
	rigidbody->SetGravityScale(0.0f);

	rigidbody->onCollisionEnter.Register(
		[this](Collider& collider)
		{ 
			std::cout << "Meow Col!" << std::endl;
		}
	);

	rigidbody->onTriggerEnter.Register(
		[this](Collider& collider)
		{ 
			std::cout << "Meow Trig!" << std::endl;
		}
	);
}

void Boomerang::OnUpdate() 
{
	if (_finished) return;

	if (!_isReturning)
	{
		transform->position = Vector2::MoveTowards(transform->position, _targetPosition, _throwSpeed * Time::GetDeltaTime());

		// 0.1f is the distance when the boomerang says, sure I reached my target
		if (transform->position.DistanceTo(_targetPosition) < 0.1f)
		{
			_isReturning = true;
		}
	}
	else
	{
		transform->position = Vector2::MoveTowards(transform->position, _thrower->transform->position, _throwSpeed * Time::GetDeltaTime());

		if (transform->position.DistanceTo(_thrower->transform->position) < 0.1f)
		{
			_finished = true;
			Events::Event e{};
			onFinish.Dispatch(e);
		}
	}
}

void Boomerang::Throw(GameObject* thrower, float speed, Math::Vector2 origin, Math::Vector2 direction)
{
	_thrower = thrower;
	_throwSpeed = speed;
	gameObject->transform->position.Set(origin);
	_targetPosition = origin + direction.GetNormalized() * _distance;
}
