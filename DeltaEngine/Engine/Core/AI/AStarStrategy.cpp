#include "AStarStrategy.hpp"

#include <algorithm>

std::vector<Math::Vector2> AStarStrategy::CalculatePath(Transform* start, Math::Vector2& end, int range, int step)
{
	InitializeGrid(start);  // Ensure grid is initialized


	Math::Vector2 tempEnd = end;
	if (!IsWalkable(end))
		tempEnd = FindClosestWalkableNode(end);
		
	// Containers
	std::unordered_map<std::shared_ptr<Node>, double> g_costs;
	std::unordered_map<std::shared_ptr<Node>, std::shared_ptr<Node>> predecessors;
    std::priority_queue<std::pair<double, std::shared_ptr<Node>>, std::vector<std::pair<double, std::shared_ptr<Node>>>, std::greater<>> pq;

    auto heuristic = [&](const Math::Vector2& a, const Math::Vector2& b) 
    {
        return std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY()); // Manhattan distance
    };
      
	// Create the start node
	std::shared_ptr<Node> startNode = CreateNode(start->position);
	if (!startNode)
		return {}; // No valid starting point

	g_costs[startNode] = 0.0;
	pq.push({0.0, startNode});

	// A* search loop
    while (!pq.empty()) 
    {
        auto [current_f_cost, current_node] = pq.top();
        pq.pop();

		// Mark node as visited
		if (current_node->tag == "visited")
			continue;
		current_node->tag = "visited";

		// Check if we reached the target
        if (current_node->position == start->position) 
            break;
            
		// Explore neighbors
        for (auto& dir : directions) 
        {
			Math::Vector2 neighborPos = current_node->position + dir;

			// Skip non-walkable or out-of-range neighbors
            if (!IsWalkable(neighborPos) || (range > 0 && (neighborPos - start->position).Magnitude() > range)) 
				continue;

            std::shared_ptr<Node> neighbor = CreateNode(neighborPos, current_node);
			if (!neighbor)
				continue; 

			double tentative_g_cost = g_costs[current_node] + 1.0;
			if (tentative_g_cost < g_costs[neighbor])
			{
				g_costs[neighbor] = tentative_g_cost;
				double h_cost = heuristic(neighbor->position, end);
				double f_cost = tentative_g_cost + h_cost;

				predecessors[neighbor] = current_node;
				pq.push({f_cost, neighbor});
			}
        }
    }

    // Reconstruct the path
	std::vector<Math::Vector2> path;
	std::shared_ptr<Node> endNode = CreateNode(end);
	if (!endNode)
		return {};	// No valid path

	for (std::shared_ptr<Node> at = endNode; at; at = predecessors[at])
	{
		if (IsWalkable(at->position))
			path.push_back(at->position);
	}

	std::reverse(path.begin(), path.end());
	return path;
}

Math::Vector2 AStarStrategy::FindClosestWalkableNode(const Math::Vector2& position) // BFS
{
    std::queue<Math::Vector2> queue;
    std::unordered_set<Math::Vector2, Vector2Hash> visited;

	Math::Vector2 snappedPos = position;
	snappedPos.SetX(std::round(snappedPos.GetX()));
	snappedPos.SetY(std::round(snappedPos.GetY()));

    queue.push(snappedPos);
	visited.insert(snappedPos);

    while (!queue.empty()) 
    {
        Math::Vector2 current = queue.front();
        queue.pop();

        if (IsWalkable(current)) 
            return current;  // Found the closest walkable node

        for (auto& dir : directions) 
        {
			Math::Vector2 neighbor = current + dir;
			neighbor.SetX(std::round(neighbor.GetX()));
			neighbor.SetY(std::round(neighbor.GetY()));

            if (visited.find(neighbor) == visited.end() && IsWithinBounds(neighbor))
            {
                queue.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }

    return snappedPos;	// Fallback: return the original position if no walkable node is found
}

bool AStarStrategy::IsWithinBounds(const Math::Vector2& position) const
{
    int normalizedX = static_cast<int>(std::round(position.GetX() - gridMinX));
    int normalizedY = gridYSize - 1 - static_cast<int>(std::round(position.GetY() - gridMinY));
	return normalizedX >= 0 && normalizedY >= 0 && normalizedX < gridXSize && normalizedY < gridYSize;
}

std::shared_ptr<Node> AStarStrategy::CreateNode(const Math::Vector2& position, std::shared_ptr<Node> parent)
{
	int x = static_cast<int>(std::round(position.GetX())); 
	int y = static_cast<int>(std::round(position.GetY()));

	if (!IsWalkable(position)) // Skip non-walkable nodes
		return nullptr;

    std::shared_ptr<Node> newNode = std::make_shared<Node>(Math::Vector2(x, y), parent);   
    newNode->tag = "normal";
    return newNode;
}

bool AStarStrategy::IsWalkable(const Math::Vector2& position)
{
	int normalizedX = static_cast<int>(std::round(position.GetX() - gridMinX));
	int normalizedY = gridYSize - 1 - static_cast<int>(std::round(position.GetY() - gridMinY));

	// Check if the tile is walkable and in bounds
	if (!IsWithinBounds(position) || !grid[normalizedY][normalizedX].walkable)
		return false;

	// Check surrounding tiles for non-walkable areas
	for (const auto& dir : directions)
	{
		Math::Vector2 neighbor = position + dir;
		int neighborX = static_cast<int>(std::round(neighbor.GetX() - gridMinX));
		int neighborY = gridYSize - 1 - static_cast<int>(std::round(neighbor.GetY() - gridMinY));

		if ((IsWithinBounds(neighbor) && !grid[neighborY][neighborX].walkable) || !IsWithinBounds(neighbor))
			return false;  // Adjacent to a non-walkable tile
	}

	return true;  // Fully walkable
}

void AStarStrategy::InitializeGrid(Transform* start)
{
	if (!grid.empty())
		return;

	start->gameObject->GetWalkableTiles(walkableTiles, wallTiles);

	int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;

	// Calculate bounds
	for (auto& tile : wallTiles)
	{
		minX = std::min(minX, static_cast<int>(tile->position.GetX()));
		maxX = std::max(maxX, static_cast<int>(tile->position.GetX()));
		minY = std::min(minY, static_cast<int>(tile->position.GetY()));
		maxY = std::max(maxY, static_cast<int>(tile->position.GetY()));
	}

	gridMinX = minX;
	gridMinY = minY;

	// Calculate grid size
	gridXSize = maxX - minX + 1;
	gridYSize = maxY - minY + 1;

	// Create the grid
	std::vector<std::vector<AStarWalkable>> tempGrid(gridYSize, std::vector<AStarWalkable>(gridXSize, {false, {0.0f, 0.0f}}));

	// Fill the grid
	for (auto& tile : walkableTiles)
	{
		int normalizedX = static_cast<int>(tile->position.GetX()) - minX;
		int normalizedY = gridYSize - 1 - (static_cast<int>(tile->position.GetY()) - minY);
		if (normalizedX >= 0 && normalizedY >= 0 && normalizedX < gridXSize && normalizedY < gridYSize)
			tempGrid[normalizedY][normalizedX] = {true, tile->position};
	}

	for (auto& tile : wallTiles)
	{
		int normalizedX = static_cast<int>(tile->position.GetX()) - minX;
		int normalizedY = gridYSize - 1 - (static_cast<int>(tile->position.GetY()) - minY);
		if (normalizedX >= 0 && normalizedY >= 0 && normalizedX < gridXSize && normalizedY < gridYSize)
			tempGrid[normalizedY][normalizedX] = {false, tile->position};
	}

	grid = tempGrid;
}