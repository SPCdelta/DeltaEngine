#pragma once

#include "Enemy.hpp"

class Skeleton : public Enemy
{
   public:
	Skeleton(const Math::Point& start_position) : Enemy(start_position, 0.5f) {}  // Skeleton moves slower

	void Update(const Math::Point& player_position) override
	{

	}
};
