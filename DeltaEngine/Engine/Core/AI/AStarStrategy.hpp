#pragma once

#include <cmath>
#include <queue>

#include <unordered_map>
#include "IAIStrategy.hpp"

class AStarStrategy : public IAIStrategy
{
   public:
	AStarStrategy() {}

	std::vector<Math::Vector2> CalculatePath(const Math::Vector2& start, const Math::Vector2& end) override
	{
		Node* startNode;
		startNode->point = start;
		startNode->f_cost = 1;
		startNode->tag = "normal";

		Node* endNode;
		endNode->point = end;
		endNode->f_cost = 1;
		endNode->tag = "normal";

		/* std::vector<Math::Vector2> path;

		// Priority queue for open set
		auto cmp = [](const Node& a, const Node& b)
		{
			return a.f_cost > b.f_cost;
		};
		std::priority_queue<Node, std::vector<Node>, decltype(cmp)> open_set(cmp);

		std::unordered_map<Math::Vector2, Math::Vector2, Hash> came_from;
		std::unordered_map<Math::Vector2, double, Hash> g_cost;
		std::unordered_map<Math::Vector2, double, Hash> f_cost;

		auto heuristic = [](const Math::Vector2& a, const Math::Vector2& b)
		{
			return std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY()); // Manhattan distance
		};

		// Initialize
		g_cost[start] = 0;
		f_cost[start] = heuristic(start, end);
		open_set.push({start, f_cost[start]});

		while (!open_set.empty())
		{
			Math::Vector2 current = open_set.top().point;
			open_set.pop();

			if (current == end)
			{
				// Reconstruct path
				while (came_from.find(current) != came_from.end())
				{
					path.push_back(current);
					current = came_from[current];
				}

				path.push_back(start);
				std::reverse(path.begin(), path.end());
				return path;
			}

			// Explore neighbors
			for (const auto& direction : directions_)
			{
				Math::Vector2 neighbor = {current.GetX() + direction.GetX(),
										  current.GetY() + direction.GetY()};

				if (!IsWalkable(neighbor))
					continue;

				double tentative_g_cost = g_cost[current] + 1;  // Assume uniform cost for simplicity

				if (tentative_g_cost < g_cost[neighbor] || g_cost.find(neighbor) == g_cost.end())
				{
					came_from[neighbor] = current;
					g_cost[neighbor] = tentative_g_cost;
					f_cost[neighbor] = tentative_g_cost + heuristic(neighbor, end);
					open_set.push({neighbor, f_cost[neighbor]});
				}
			}
		}

		return path;  // Return empty path if no path exists */

		//graph.untag_all();
        std::unordered_map<Node*, double> g_costs;
        std::unordered_map<Node*, Node*> predecessors;
        std::priority_queue<std::pair<double, Node*>, std::vector<std::pair<double, Node*>>, std::greater<>> pq;

        for (auto& node : graph) 
            g_costs[&node] = std::numeric_limits<double>::infinity();
        
        g_costs[startNode] = 0.0;
		pq.push({0.0, startNode});

        while (!pq.empty()) 
        {
            auto [current_f_cost, current_node] = pq.top();
            pq.pop();

            if (current_node->tag != "visited") 
                current_node->tag = "visited";

            if (current_node == endNode) 
                break;
            
            for (auto edge : *current_node) 
            {
                auto* neighbor = &edge.to();
				if (neighbor->tag != "visited")
					neighbor->tag = "visited";
            
                double tentative_g_cost = g_costs[current_node] + edge.weight();

                if (tentative_g_cost < g_costs[neighbor]) 
                {
                    g_costs[neighbor] = tentative_g_cost;
                    double h_cost = manhattan_distance(neighbor->location(), endNode->point);
                    double f_cost = tentative_g_cost + h_cost;

                    predecessors[neighbor] = current_node;
                    pq.push({f_cost, neighbor});
                }
            }
        }

        std::vector<Math::Vector2> path;
        for (Node* at = const_cast<Node*>(endNode); at != nullptr; at = predecessors[at]) 
        {
			path.push_back(at->point);
			at->tag = "path";
        }

        std::reverse(path.begin(), path.end());
        return path;
	}

   private:
	struct Node
	{
		Math::Vector2 point;
		double f_cost;
		std::string tag;
	};

	struct Hash
	{
		size_t operator()(const Math::Vector2& p) const
		{
			return std::hash<int>()(p.GetX()) ^ std::hash<int>()(p.GetY());
		}
	};

	//const std::vector<std::vector<int>>& grid_;
	const std::vector<Math::Vector2> directions_ = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	float manhattan_distance(const Math::Vector2& a, const Math::Vector2& b)
	{
		return std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY());
	}

	/*bool IsWalkable(const Math::Point& point) const
	{
		return point.GetX() >= 0 && point.GetX() < grid_.size() && point.GetY() >= 0 && point.GetY() < grid_[0].size() && grid_[point.GetX()][point.GetY()] != 1;  // 1 indicates non-walkable
	}*/
};
