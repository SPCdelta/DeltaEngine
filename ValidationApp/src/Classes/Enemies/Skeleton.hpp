#pragma once

#include "Enemy.hpp"
#include "../Projectiles/Projectile.hpp"

class Skeleton : public Enemy
{
public:
	Skeleton(Math::Vector2* position, Transform& transform, float speed = 2.5f, int health = 20, int damage = 0, int range = 50, int step = 5) 
        : Enemy(position, speed, health, damage, range, step), transform(transform) { }

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override
	{
		if (_dead)
			return;

        Math::Vector2 distanceToPlayer = transform.position - player_position.position;
        if (distanceToPlayer.Magnitude() <= _attackRange)
        {
            float deltaTime = Time::GetDeltaTime();
            _lastAttackTime += deltaTime;

            if (_lastAttackTime >= _attackCooldown)
            {
                ShootArrow(player_position);
                _lastAttackTime = 0.0f; 

                _sfx->SetClip("bow_shoot");
				_sfx->Play();
            }
        }
	}

    void ShootArrow(Transform& player_position)
    {
        std::shared_ptr<GameObject> arrowObj = transform.gameObject->Instantiate();
		arrowObj->AddComponent<CircleCollider>()->SetTrigger(true);
		arrowObj->AddComponent<Rigidbody>()->SetGravityScale(0.0f);
		arrowObj->AddComponent<Lifetime>(DEFAULT_LIFETIME);
		arrowObj->transform->position.Set(transform.position);
        arrowObj->AddComponent<Projectile>()->SetProjectileData({"arrow", 5, 5.0f, transform.position.DirectionTo(player_position.position)});
		arrowObj->SetTag("skeleton_arrow");
    }

    void Die(Audio::SFXSource* _sfx) override
    {
        _dead = true;
		_sfx->SetClip("skeleton_death");
		_sfx->Play();
    }

private:
	Transform& transform;

	float _attackRange {20.0f};
	float _attackCooldown {2.0f};
	float _lastAttackTime {0.0f};
};
