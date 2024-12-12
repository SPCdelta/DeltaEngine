#pragma once

#include "Enemy.hpp"

class Goblin : public Enemy
{
   public:
	Goblin(Math::Vector2* position, int health) : Enemy(position, 2.0f, health) {}  // Goblin moves 1 unit per update

	void Update(const Math::Vector2& player_position) override
	{

	}
};
