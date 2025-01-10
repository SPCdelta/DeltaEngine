#include "AStarStrategy.hpp"

#include <algorithm>

std::vector<Math::Vector2> AStarStrategy::CalculatePath(Transform* start, Math::Vector2& end, int range, int step)
{
	InitializeGrid(start);  // Ensure grid is initialized
		
	std::unordered_map<Node*, double> g_costs;
	std::unordered_map<Node*, Node*> predecessors;
    std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<>> pq;

    auto heuristic = [&](const Math::Vector2& a, const Math::Vector2& b) 
    {
        return std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY()); // Manhattan distance
    };
      
    Node* startNode = CreateNode(start->position);
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

            Node* neighbor;
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
	for (Node* at = endNode; at; at = predecessors[at])
	{
		path.push_back(at->position);
	}

	std::reverse(path.begin(), path.end());
	return path;
}

Node* AStarStrategy::CreateNode(const Math::Vector2& position, Node* parent)
{
    Node* newNode = new Node(position, parent);   
    newNode->tag = "normal";
    return newNode;
}

bool AStarStrategy::IsWalkable(const Math::Vector2& position)
{
	int normalizedX = position.GetX() - gridMinX;
	int normalizedY = position.GetY() - gridMinY;

	// Check bounds
	if (normalizedX < 0 || normalizedY < 0 || normalizedY >= gridYSize || normalizedX >= gridXSize)
	{
		return false;  // Out of bounds
	}

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
	for (auto& tile : walkableTiles)
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

	int bp = 0;
	grid = tempGrid;
}