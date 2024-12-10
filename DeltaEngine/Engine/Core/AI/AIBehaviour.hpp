#pragma once

#include <vector>

#include "../Math/Point.hpp"
#include "IAIStrategy.hpp"

class AIBehaviour
{
   public:
	AIBehaviour(std::shared_ptr<IAIStrategy> strategy, Math::Vector2* pos, Math::Vector2* playerPos) : 
		strategy_(strategy), position_(pos), _playerPosition(playerPos) {}

	void Update()
	{
		if (!position_ || !_playerPosition)
			return;

		// TODO path is always empty
		path_ = strategy_->CalculatePath(*position_, *_playerPosition);

		if (!path_.empty())
		{
			// Move to the next point in the path
			position_ = &path_.front();
			path_.erase(path_.begin());
		}
	}

	Math::Vector2* GetPosition() const { return position_; }
	void SetPosition(Math::Vector2* position) { position_ = position; }
	void SetPlayerPosition(Math::Vector2* position) { _playerPosition = position; }

   private:
	std::shared_ptr<IAIStrategy> strategy_;
	std::vector<Math::Vector2> path_;

	Math::Vector2* position_;
	Math::Vector2* _playerPosition;
};

// TODO
/* std::vector<std::vector<int>> dungeon = {
    {0, 0, 0, 0, 1},
    {0, 1, 1, 0, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

Math::Point player_position = {4, 4};
Math::Point enemy_start = {0, 0};

AStarStrategy astar(dungeon);
AIBehaviour enemy(&astar);
enemy.SetPosition(enemy_start);

for (int i = 0; i < 10; ++i)
{
	enemy.Update(player_position);
	Math::Point enemy_position = enemy.GetPosition();
	std::cout << "Enemy Position: (" << enemy_position.x << ", "
			  << enemy_position.y << ")\n";
}*/
