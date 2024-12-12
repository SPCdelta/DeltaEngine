#pragma once

#include <cmath>
#include <queue>

#include <unordered_map>
#include "IAIStrategy.hpp"

class AStarStrategy : public IAIStrategy
{
   public:
	AStarStrategy() 
    {

    }

	std::vector<Math::Vector2> CalculatePath(const Math::Vector2& start, const Math::Vector2& end)
	{
        auto compare = [](const Node* lhs, const Node* rhs) 
        { 
            return lhs->fCost() > rhs->fCost(); 
        };

        std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);

        auto heuristic = [&](const Math::Vector2& a, const Math::Vector2& b) 
        {
            return std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY()); // Manhattan distance
        };

        Node* startNode = CreateNode(start, 0.0f, heuristic(start, end));
        openSet.push(startNode);

        std::unordered_map<Math::Vector2, bool, Vector2Hash> closedSet;

        int maxIterations = 10000;	// Limit iterations to prevent freezes
		int iterations = 0;
        while (!openSet.empty()) 
        {
            Node* current = openSet.top();
            openSet.pop();

            if (++iterations > maxIterations || current->position == end)
			{
				std::vector<Math::Vector2> path;
				while (current)
				{
					path.push_back(current->position);
					current = current->parent;
				}

				std::reverse(path.begin(), path.end());
				return path;
			}

            closedSet[current->position] = true;

			const std::vector<Math::Vector2> directions = 
            {
				{1, 0}, {-1, 0},  {0, 1},  {0, -1},	
				{1, 1}, {-1, -1}, {1, -1}, {-1, 1}	 
			};

            for (const auto& dir : directions) 
            {
                Math::Vector2 neighborPos = current->position + dir;

                if (closedSet.find(neighborPos) != closedSet.end()) continue; // Already visited
                if (!IsWalkable(neighborPos)) continue; // Wall detected, cannot walk here

                float gCost = current->gCost + 1.0f;
                Node* neighbor = CreateNode(neighborPos, gCost, heuristic(neighborPos, end), current);
                if (neighbor) openSet.push(neighbor);
            }
        }

        return {}; // No path found
	}

   private:
        Node* CreateNode(const Math::Vector2& position, float gCost, float hCost, Node* parent = nullptr)
        {
            Node* newNode = new Node(position, gCost, hCost, parent);   
            return newNode;
        }

        bool IsWalkable(const Math::Vector2& position)
        {
			bool isWalkable = true;	

			//_rigidbody.onTriggerEnter.Register(
			//	[&](Collider& collider)
			//	{
			//		// Check if the collider is something that blocks movement, like a wall or obstacle
			//		if (collider.transform.gameObject->GetTag() == "Wall")	
			//		{
			//			isWalkable = false;	
			//		}
			//	});

			//_rigidbody.onTriggerExit.Register(
			//	[&](Collider& collider)
			//	{
			//		if (collider.transform.gameObject->GetTag() == "Wall")	 
			//		{
			//			isWalkable = true; 
			//		}
			//	});

			// If collision with a wall, return false (not walkable)
			return isWalkable;
        }
};
