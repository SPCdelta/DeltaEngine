#pragma once

#include "Enemy.hpp"

class Skeleton : public Enemy
{
   public:
	Skeleton(Math::Vector2* position, int health) : Enemy(position, 2.5f, health) {}

	void Update(const Math::Vector2& player_position) override
	{

	}
};
