#pragma once

#include <cstdlib>

#include "Enemy.hpp"

class Slime : public Enemy
{
   public:
	Slime(const Math::Point& start_position) : Enemy(start_position, 0.8f) {}

	void Update(const Math::Point& player_position) override
	{
		// Add randomness to movement
		Math::Point direction = GetDirectionTo(player_position);
		direction.SetX(direction.GetX() + (std::rand() % 3 - 1)); // -1, 0, or 1
		direction.SetY(direction.GetY() + (std::rand() % 3 - 1));

		position_.SetX(position_.GetX() + (direction.GetX() * speed_)); 
		position_.SetY(position_.GetY() + (direction.GetY() * speed_));
	}
};

// TODO
/* void GameUpdate()
{
	Math::Point player_position{10, 10};  // Example player position

	// Create enemies
	Goblin goblin({5, 5});
	Skeleton skeleton({15, 15});
	Slime slime({20, 5});

	std::vector<Enemy*> enemies = {&goblin, &skeleton, &slime};

	// Game loop
	for (int i = 0; i < 20; ++i)
	{  // Simulate 20 updates
		std::cout << "Update " << i + 1 << ":\n";
		for (Enemy* enemy : enemies)
		{
			enemy->Update(player_position);
			Math::Point pos = enemy->GetPosition();
			std::cout << "Enemy at (" << pos.x << ", " << pos.y << ")\n";
		}
		std::cout << "----\n";
	}
}*/