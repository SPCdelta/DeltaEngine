#include "Skeleton.hpp"

Skeleton::Skeleton(Math::Vector2* position, GameObject* obj, float speed, int health, int damage, int range, int step)
	: Enemy(position, speed, health, damage, range, step), 
	  gameObject(obj)
{

}

Skeleton::~Skeleton()
{
	gameObject = nullptr;
}

void Skeleton::Update(Transform& player_position, Audio::SFXSource* _sfx)
{
	if (_dead)
		return;

	Math::Vector2 distanceToPlayer = gameObject->transform->position - player_position.position;
	if (distanceToPlayer.Magnitude() <= _attackRange)
	{
		float deltaTime = Time::GetDeltaTime();
		_lastAttackTime += deltaTime;

		if (_lastAttackTime >= _attackCooldown)
		{
			ShootArrow(player_position);
			_lastAttackTime = 0.0f;

			if (_sfx)
			{
				_sfx->SetClip("bow_shoot");
				_sfx->SetVolume(5);
				_sfx->Play();
			}
		}
	}
}

void Skeleton::ShootArrow(Transform& player_position)
{
	std::shared_ptr<GameObject> arrowObj = gameObject->Instantiate();
	arrowObj->transform->position.Set(gameObject->transform->position);
	arrowObj->AddComponent<Projectile>()->SetProjectileData(
	{
		"arrow", 
		5, 
		5.0f,
		gameObject->transform->position.DirectionTo(player_position.position)
	});
	arrowObj->SetTag("skeleton_arrow");
}

void Skeleton::Die(Audio::SFXSource* _sfx)
{
	_dead = true;

	if (_sfx)
	{
		_sfx->SetClip("skeleton_death");
		_sfx->SetVolume(5);
		_sfx->Play();
	}
}