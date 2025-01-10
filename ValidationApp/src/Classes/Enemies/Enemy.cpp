#include "Enemy.hpp"

Enemy::Enemy(Math::Vector2* position, float speed, int health, int damage, int range, int step)
	: position_(position),
	  speed_(speed),
	  _health(health),
	  _damage(damage),
	  range_(range),
	  step_(step)
{

}

Enemy::~Enemy()
{
	position_ = nullptr;
}

Math::Vector2* Enemy::GetPosition() const
{
	return position_;
}

int Enemy::GetDamage() const
{
	return _damage;
}

void Enemy::SetDamage(int damage)
{
	_damage = damage;
}

int Enemy::GetHealth() const
{
	return _health;
}

void Enemy::SetHealth(int health)
{
	_health = health;
}

int Enemy::GetRange() const
{
	return range_;
}

int Enemy::GetStep() const
{
	return step_;
}

float Enemy::GetSpeed() const
{
	return speed_;
}

bool Enemy::IsDead() const
{
	return _dead;
}