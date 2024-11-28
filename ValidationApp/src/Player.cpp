#include "Player.hpp"


void Player::SetShield(int shield) {
	_shield = shield;
}

void Player::SetAttackDamage(int damage) {
	_attackDamage = damage;
}

void Player::SetSpeed(int speed) {
	_speed = speed;
}

void Player::SetHealth(int health) {
	_health = health;
}

void Player::AddHealth(int health) {
	_health += health;
}


int Player::GetShield() const
{
	return _shield;
}

int Player::GetAttackDamage() const
{
	return _attackDamage;
}

int Player::GetSpeed() const
{
	return _speed;
}

int Player::GetHealth() const
{
	return _health;
}
