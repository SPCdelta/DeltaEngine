#pragma once

#include "Enemy.hpp"
#include "../Projectiles/Projectile.hpp"

class Skeleton : public Enemy
{
   public:
	Skeleton(Math::Vector2* position, GameObject* obj, float speed = 2.5f, int health = 20, int damage = 0, int range = 50, int step = 5) 
        : Enemy(position, speed, health, damage, range, step), gameObject(obj) {} 

    ~Skeleton()
    {
        gameObject = nullptr;
    }

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override
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
					_sfx->SetClip("Assets\\Audio\\SFX\\Bow_shoot.mp3");
					_sfx->SetVolume(5);
					_sfx->Play();
                }
            }
        }
	}

    void ShootArrow(Transform& player_position)
    {
        std::shared_ptr<GameObject> arrowObj = gameObject->Instantiate();
		arrowObj->transform->position.Set(gameObject->transform->position);
        arrowObj->AddComponent<Projectile>()->SetProjectileData({"arrow", 5, 5.0f, gameObject->transform->position.DirectionTo(player_position.position)});
		arrowObj->SetTag("skeleton_arrow");
    }

    void Die(Audio::SFXSource* _sfx) override
    {
        _dead = true;

        if (_sfx)
        {
            _sfx->SetClip("Assets\\Audio\\SFX\\Skeleton_death.mp3");
			_sfx->SetVolume(5);
		    _sfx->Play();
        }
    }

   private:
	GameObject* gameObject {nullptr};

	float _attackRange {20.0f};
	float _attackCooldown {2.0f};
	float _lastAttackTime {0.0f};
};
