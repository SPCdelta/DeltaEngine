#pragma once

#include "Enemy.hpp"

class Goblin : public Enemy
{
   public:
	Goblin(const Math::Point& start_position) : Enemy(start_position, 1.0f) {}  // Goblin moves 1 unit per update

	void Update(const Math::Point& player_position) override
	{
		MoveTowards(player_position);
	}
};
