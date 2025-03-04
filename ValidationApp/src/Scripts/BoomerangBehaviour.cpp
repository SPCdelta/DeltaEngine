#include "BoomerangBehaviour.hpp"

void BoomerangBehaviour::OnStart() 
{
	Projectile::OnStart();
}

void BoomerangBehaviour::OnUpdate()
{
	Projectile::OnUpdate();
	if (_finished) return;

	// Rotations Login
	transform->rotation += (360.0f * _rotationsPerSecond) * Time::GetDeltaTime();
	if (transform->rotation > 360.0f) transform->rotation -= 360.0f;

	// Speed Logic
	if (_isReturning)
	{
		// To Player
		transform->position = Vector2::MoveTowards(transform->position, _thrower->transform->position, _throwSpeed * Time::GetDeltaTime());
		if (transform->position.DistanceTo(_thrower->transformRef.position) < 1.0f)
		{
			_finished = true;
			Events::Event e{};
			onFinish.Dispatch(e);
		}
	}
	else
	{
		// To Target
		if (transform->position.DistanceTo(_originPosition) >= _distance)
			Return();
	}
}

void BoomerangBehaviour::Throw(std::shared_ptr<GameObject> thrower, float speed, Math::Vector2 origin, Math::Vector2 direction)
{
	std::cout << this << std::endl;
	audioSource = transform->gameObject->AddComponent<Audio::SFXSource>("boomerang_throw", false, -1);

	_thrower = thrower;
	_throwSpeed = speed;
	transform->position.Set(origin);

	_originPosition = origin;
	_targetPosition = origin + direction.GetNormalized() * _distance;

	SetProjectileData({ "boomerang", 35, speed, direction.GetNormalized() });

	rigidbody->onTriggerEnter.Register
	(
		[this](Collider& collider)
		{ 
			if (collider.transform.gameObject->GetTag() != "player")
			{
				std::cout << "Reached a Target" << std::endl;
				Return();
			}
		}
	);

	audioSource->Loop(true);
	audioSource->Play();
}

void BoomerangBehaviour::Return() 
{
	if (_isReturning)
		return;

	_isReturning = true;
	rigidbody->SetVelocity({0.0f, 0.0f});
}
