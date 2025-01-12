#pragma once

#include "Enemy.hpp"
#include "../Projectiles/Projectile.hpp"

class Skeleton : public Enemy
{
public:
	Skeleton(Math::Vector2* position, Transform& transform, float speed = 1.5f, int health = 20, int damage = 0, int range = 10, int step = 5);
    ~Skeleton();

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override;
	void Die(Audio::SFXSource* _sfx) override;

    void ShootArrow(Transform& player_position);

private:
	Transform& transform;

	float _attackRange {8.0f};
	float _attackCooldown {2.0f};
	float _lastAttackTime {0.0f};
};
