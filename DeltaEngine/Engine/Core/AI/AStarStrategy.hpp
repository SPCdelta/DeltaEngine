#pragma once

#include <cmath>
#include <queue>
#include <unordered_map>

#include "IAIStrategy.hpp"

class AStarStrategy : public IAIStrategy
{
   public:
	AStarStrategy() = default;

	std::vector<Math::Vector2> CalculatePath(Math::Vector2& start, Math::Vector2& end, int range = 500, int step = 50) override;

   private:
        Node* CreateNode(const Math::Vector2& position, Node* parent = nullptr);
        void InitializeNodesAround(Math::Vector2 center, int range, int step, std::unordered_map<Math::Vector2, Node*, Vector2Hash>& nodeMap);

        bool IsWalkable(const Math::Vector2& position);
};
