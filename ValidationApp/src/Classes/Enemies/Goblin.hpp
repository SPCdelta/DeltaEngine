#pragma once

#include "Enemy.hpp"

class Goblin : public Enemy
{
public:
	Goblin(Math::Vector2* position, float speed = 1.5f, int health = 25, int damage = 10, int range = 15, int step = 5);

	void Update(Transform& player_position, Audio::SFXSource* _sfx) override;
	void Die(Audio::SFXSource* _sfx) override;
};
