#pragma once

#include "Enemy.hpp"
#include "../Projectiles/Projectile.hpp"

class Skeleton : public Enemy
{
   public:
	Skeleton(Math::Vector2* position, GameObject* obj) : Enemy(position, 2.5f, 20, 0, 50, 5), gameObject(obj) {} 

	void Update(const Math::Vector2& player_position, Audio::SFXSource* _sfx) override
	{
		if (_dead)
			return;

        Math::Vector2 distanceToPlayer = gameObject->transform->position - player_position;
        if (distanceToPlayer.Magnitude() <= _attackRange)
        {
            float deltaTime = Time::GetDeltaTime();
            _lastAttackTime += deltaTime;

            if (_lastAttackTime >= _attackCooldown)
            {
                ShootArrow(player_position, _sfx);
                _lastAttackTime = 0.0f; 
            }
        }
	}

    void ShootArrow(const Math::Vector2& player_position, Audio::SFXSource* _sfx)
    {
        std::shared_ptr<GameObject> arrowObj = gameObject->Instantiate();
		arrowObj->transform->position.Set(gameObject->transform->position);
        arrowObj->AddComponent<Projectile>()->SetProjectileData({"arrow", 5, 5.0f, gameObject->transform->position.DirectionTo(player_position)});
		arrowObj->SetTag("skeleton_arrow");

        _sfx->SetClip("Assets\\Audio\\SFX\\Bow_shoot.mp3");
        _sfx->Play();
    }

   private:
	GameObject* gameObject {nullptr};

	float _attackRange {20.0f};
	float _attackCooldown {2.0f};
	float _lastAttackTime {0.0f};
};
