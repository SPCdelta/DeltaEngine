#pragma once

#include <cstdlib>

#include "Enemy.hpp"

class Slime : public Enemy
{
   public:
	Slime(Math::Vector2* position) : Enemy(position, 1.0f, 5, 50, 10) {}

	void Update(const Math::Vector2& player_position) override
	{

	}
};
