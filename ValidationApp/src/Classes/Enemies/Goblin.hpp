#pragma once

#include "Enemy.hpp"

class Goblin : public Enemy
{
   public:
	Goblin(Math::Vector2* position) : Enemy(position, 2.0f, 15, 200, 50) {}

	void Update(const Math::Vector2& player_position) override
	{

	}
};
