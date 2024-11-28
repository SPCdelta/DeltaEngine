#pragma once
class Player
{
   public:
	Player(int shield, int damage, int speed, int health)
		: _shield{shield}, _attackDamage{damage}, _speed{speed}, _health{health}
	{
	}
	void SetShied(int shield);
	void SetAttackDamage(int damage);
	void SetSpeed(int speed);
	void SetHealth(int health);

	int GetShield() const;
	int GetAttackDamage() const;
	int GetSpeed() const;
	int GetHealth() const;
   private:
	int _shield;
	int _attackDamage;
	int _speed;
	int _health;
};
