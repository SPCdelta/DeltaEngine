#pragma once

#include "Engine/Delta.hpp"

enum class EnemyType
{
	Goblin,
	Skeleton,
	Slime,
};

class Enemy
{
   public:
	Enemy(Math::Vector2* position, float speed, int health, int damage, int range, int step) : position_(position), speed_(speed), _health(health), _damage(damage),
		range_(range), step_(step) {}

	virtual void Update(Transform& player_position, Audio::SFXSource* _sfx) = 0;

	Math::Vector2* GetPosition() const { return position_; }

	int GetDamage() const { return _damage; }
	void SetDamage(int damage) { _damage = damage; }

	int GetHealth() const { return _health; }
	void SetHealth(int health) { _health = health; }

	void Die() { _dead = true; }

	int GetRange() const { return range_; }
	int GetStep() const { return step_; }
	float GetSpeed() const { return speed_; }

	static std::string TypeToString(EnemyType type)
	{
		switch (type)
		{
			case EnemyType::Goblin:
				return "goblin";
			case EnemyType::Skeleton:
				return "skeleton";
			case EnemyType::Slime:
			default:
				return "slime";
		}
	}

	static EnemyType StringToType(std::string type)
	{
		if (type == "goblin") 
		{
			return EnemyType::Goblin;
		}
		else if (type == "skeleton")
		{
			return EnemyType::Skeleton;
		}
		else 
		{
			return EnemyType::Slime;
		}
	}

   private:
	int _health;
	int _damage;

	int range_;
	int step_;

   protected:
	Math::Vector2* position_;
	float speed_;

	bool _dead{false};
};
