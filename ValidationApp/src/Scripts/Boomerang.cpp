#include "Boomerang.hpp"

void Boomerang::OnStart() 
{
	Projectile::OnStart();
}

void Boomerang::OnUpdate() 
{
	Projectile::OnUpdate();
	if (_finished) return;

	// Rotations per second
	transform->rotation += (360.0f * _rotationsPerSecond) * Time::GetDeltaTime();
	if (transform->rotation > 360.0f) transform->rotation -= 360.0f;

	if (!_isReturning)
	{
		// 1.0f is the distance when the boomerang says, sure I reached my target
		if (transform->position.DistanceTo(_targetPosition) < 1.0f)
		{
			Return();
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
	audioSource = gameObject->AddComponent<Audio::SFXSource>("Assets\\Audio\\SFX\\boomerang.mp3", false, -1);

	_thrower = thrower;
	_throwSpeed = speed;
	gameObject->transform->position.Set(origin);
	_targetPosition = origin + direction.GetNormalized() * _distance;

	SetProjectileData({ "boomerang", 35, speed, direction.GetNormalized() });

	rigidbody->onTriggerEnter.Register(
		[this](Collider& collider)
		{ 
			if (collider.transform.gameObject->GetTag() != "player")
			{
				Return();
			}
		}
	);

	audioSource->Loop(true);
	audioSource->Play();
}

void Boomerang::Return() 
{
	_isReturning = true;
	rigidbody->SetVelocity({0.0f, 0.0f});
}
