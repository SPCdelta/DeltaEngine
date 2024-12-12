#pragma once

#include <cstdlib>

#include "Enemy.hpp"

class Slime : public Enemy
{
   public:
	Slime(Math::Vector2* position, int health) : Enemy(position, 1.0f, health) {}

	void Update(const Math::Vector2& player_position) override
	{

	}
};
