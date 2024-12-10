#pragma once

#include <cstdlib>

#include "Enemy.hpp"

class Slime : public Enemy
{
   public:
	Slime(const Math::Point& start_position) : Enemy(start_position, 0.8f) {}

	void Update(const Math::Point& player_position) override
	{

	}
};
