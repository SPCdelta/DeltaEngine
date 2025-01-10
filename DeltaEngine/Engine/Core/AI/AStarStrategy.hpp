#pragma once

#include <cmath>
#include <queue>
#include <unordered_map>

#include "IAIStrategy.hpp"
#include "../../Systems/AStarSystem.hpp"

class AStarStrategy : public IAIStrategy
{
public:
	AStarStrategy() = default;

	std::vector<Math::Vector2> CalculatePath(Transform* start, Math::Vector2& end, int range, int step) override;

	void InitializeGrid(Transform* start);
	bool IsWalkable(const Math::Vector2& position) override;

private:
    Node* CreateNode(const Math::Vector2& position, Node* parent = nullptr);

    using Grid = std::vector<std::vector<AStarWalkable>>;
	Grid grid;	
	int gridMinX, gridMinY, gridXSize, gridYSize {0};

	std::vector<Transform*> walkableTiles;
	std::vector<Transform*> wallTiles;
};
