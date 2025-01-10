#pragma once

#include <cmath>
#include <queue>
#include <unordered_map>

#include "IAIStrategy.hpp"

class AStarStrategy : public IAIStrategy
{
public:
    AStarStrategy() = default;

	std::vector<Math::Vector2> CalculatePath(Transform* start, Math::Vector2& end, int range, int step) override;

private:
    Node* CreateNode(const Math::Vector2& position, Node* parent = nullptr);
    void InitializeNodesAround(Transform* center, int range, int step, std::unordered_map<Math::Vector2, Node*, Vector2Hash>& nodeMap);

    std::vector<Transform*> tiles;
    bool IsWalkable(const Math::Vector2& position);
};
