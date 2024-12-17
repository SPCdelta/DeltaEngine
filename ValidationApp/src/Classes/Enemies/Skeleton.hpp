#pragma once

#include "Enemy.hpp"

class Skeleton : public Enemy
{
   public:
	Skeleton(Math::Vector2* position) : Enemy(position, 2.5f, 10, 500, 50) {}

	void Update(const Math::Vector2& player_position) override
	{

	}
};
