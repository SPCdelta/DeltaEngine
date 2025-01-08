#pragma once

#include "Engine/Delta.hpp"

enum class EnemyType
{
	Goblin,
	Skeleton,
	Slime,
	Boss
};

class Enemy
{
public:
	Enemy(Math::Vector2* position, float speed, int health, int damage, int range, int step);
	~Enemy();

	virtual void Update(Transform& player_position, Audio::SFXSource* _sfx) = 0;

	Math::Vector2* GetPosition() const;

	int GetDamage() const;
	void SetDamage(int damage);

	int GetHealth() const;
	void SetHealth(int health);

	virtual void Die(Audio::SFXSource* _sfx) = 0;

	int GetRange() const;
	int GetStep() const;
	float GetSpeed() const;

	static std::string TypeToString(EnemyType type)
	{
		switch (type)
		{
			case EnemyType::Goblin:
				return "goblin";
			case EnemyType::Skeleton:
				return "skeleton";
			case EnemyType::Slime:
				return "slime";
			case EnemyType::Boss:
			default:
				return "boss";
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
		else if (type == "slime")
		{
			return EnemyType::Slime;
		}
		else 
		{
			return EnemyType::Boss;
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
