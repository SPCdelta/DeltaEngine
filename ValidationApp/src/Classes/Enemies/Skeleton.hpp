#pragma once

#include "Enemy.hpp"

class Skeleton : public Enemy
{
   public:
	Skeleton(const Math::Point& start_position) : Enemy(start_position, 0.5f) {}  // Skeleton moves slower

	void Update(const Math::Point& player_position) override
	{
		// Skeleton moves every 2 updates
		static int update_count = 0;
		if (++update_count % 2 == 0)
		{
			MoveTowards(player_position);
		}
	}
};
