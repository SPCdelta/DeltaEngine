#pragma once
class Player
{
   public:
	Player(int shield, int damage, int speed, int health)
		: _shield{shield}, _attackDamage{damage}, _speed{speed}, _health{health}
	{
	}
	void SetShield(int shield);
	void SetAttackDamage(int damage);
	void SetSpeed(int speed);
	void SetHealth(int health);

	void AddHealth(int health);

	int GetShield() const;
	int GetAttackDamage() const;
	int GetSpeed() const;
	int GetHealth() const;
	const int _maxHealth = 100;
   private:
	int _shield;
	int _attackDamage;
	int _speed;
	int _health;
};
