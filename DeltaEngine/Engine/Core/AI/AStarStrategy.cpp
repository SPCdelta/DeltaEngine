#include "AStarStrategy.hpp"

#include <algorithm>

std::vector<Math::Vector2> AStarStrategy::CalculatePath(Transform* start, Math::Vector2& end, int range, int step)
{
	InitializeGrid(start);  // Ensure grid is initialized

	if (!IsWalkable(end))
		end = FindClosestWalkableNode(end);
		
	std::unordered_map<Node*, double> g_costs;
	std::unordered_map<Node*, Node*> predecessors;
    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<>> pq;

    auto heuristic = [&](const Math::Vector2& a, const Math::Vector2& b) 
    {
        return std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY()); // Manhattan distance
    };
      
    Node* startNode = CreateNode(start->position);
	if (startNode == nullptr)
		return {};

	g_costs[startNode] = 0.0;
	pq.push({0.0, startNode});

    while (!pq.empty()) 
    {
        auto [current_f_cost, current_node] = pq.top();
        pq.pop();

        if (current_node->tag != "visited") 
            current_node->tag = "visited";

        if (current_node->position == end) 
            break;

        // N, E, S, W and diagonals
        const std::vector<Math::Vector2> directions = 
        {
			{1, 0}, {-1, 0},  {0, 1},  {0, -1},	
			{1, 1}, {-1, -1}, {1, -1}, {-1, 1}	 
		};
            
        for (auto& dir : directions) 
        {
			Math::Vector2 neighborPos = current_node->position + dir; 

            if (!IsWalkable(neighborPos) || (range > 0 && (neighborPos - start->position).Magnitude() > range)) 
				continue;

            Node* neighbor = CreateNode(neighborPos, current_node);
			if (neighbor == nullptr)
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

    std::vector<Math::Vector2> path;
	Node* endNode = CreateNode(end);
	if (endNode == nullptr)
		return {};

	for (Node* at = endNode; at; at = predecessors[at])
		path.push_back(at->position);

	std::reverse(path.begin(), path.end());
	return path;
}

Math::Vector2 AStarStrategy::FindClosestWalkableNode(const Math::Vector2& position) // BFS
{
    std::queue<Math::Vector2> queue;
    std::unordered_set<Math::Vector2, Vector2Hash> visited;

    queue.push(position);
    visited.insert(position);

    while (!queue.empty()) 
    {
        Math::Vector2 current = queue.front();
        queue.pop();

        if (IsWalkable(current)) 
            return current;  // Found the closest walkable node

        // N, E, S, W and diagonals
        const std::vector<Math::Vector2> directions = 
        {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1},  
            {1, 1}, {-1, -1}, {1, -1}, {-1, 1} 
        };

        for (auto& dir : directions) 
        {
            Math::Vector2 neighbor = current + dir;

            if (visited.find(neighbor) == visited.end() && IsWithinBounds(neighbor)) 
            {
                queue.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }

    return position;  // Fallback: return the original position if no walkable node is found
}

bool AStarStrategy::IsWithinBounds(const Math::Vector2& position)
{
    int normalizedX = static_cast<int>(std::round(position.GetX() - gridMinX));
    int normalizedY = static_cast<int>(std::round(position.GetY() - gridMinY));
    return normalizedX >= 0 && normalizedY >= 0 && normalizedX < gridXSize && normalizedY < gridYSize;
}


Node* AStarStrategy::CreateNode(const Math::Vector2& position, Node* parent)
{
	int x = static_cast<int>(std::round(position.GetX())); 
	int y = static_cast<int>(std::round(position.GetY()));

	if (!IsWalkable(position))
		return nullptr;

    Node* newNode = new Node(Math::Vector2(x, y), parent);   
    newNode->tag = "normal";
    return newNode;
}

bool AStarStrategy::IsWalkable(const Math::Vector2& position)
{
	int normalizedX = static_cast<int>(std::round(position.GetX() - gridMinX));
	int normalizedY = static_cast<int>(std::round(position.GetY() - gridMinY));

	// Check bounds
	if (!IsWithinBounds(position))
		return false;  // Out of bounds

	// Return the walkability status
	return grid[normalizedY][normalizedX].walkable;
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
		int normalizedX = tile->position.GetX() - minX;
		int normalizedY = tile->position.GetY() - minY;
		tempGrid[normalizedY][normalizedX] = {true, tile->position};
	}

	for (auto& tile : wallTiles)
	{
		int normalizedX = tile->position.GetX() - minX;
		int normalizedY = tile->position.GetY() - minY;
		tempGrid[normalizedY][normalizedX] = {false, tile->position};
	}

	int bp = 0;
	grid = tempGrid;
}