#pragma once

#include "Enemy.hpp"
#include "../Projectiles/Projectile.hpp"

class Skeleton : public Enemy
{
public:
	Skeleton(Math::Vector2* position, GameObject* obj, float speed = 2.5f, int health = 20, int damage = 0, int range = 50, int step = 5);
    ~Skeleton();

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override;
	void Die(Audio::SFXSource* _sfx) override;

    void ShootArrow(Transform& player_position);

private:
	GameObject* gameObject {nullptr};

	float _attackRange {20.0f};
	float _attackCooldown {2.0f};
	float _lastAttackTime {0.0f};
};
