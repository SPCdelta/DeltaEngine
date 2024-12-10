#pragma once

#include <cmath>
#include <queue>

#include <unordered_map>
#include "IAIStrategy.hpp"

class AStarStrategy : public IAIStrategy
{
   public:
	AStarStrategy() {}

	std::vector<Math::Vector2> CalculatePath(const Math::Vector2& start, const Math::Vector2& end)
	{
		auto cmp = [](Node* a, Node* b)
		{
			return a->f_cost() > b->f_cost();
		};

		std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> open_list(cmp);
		std::unordered_set<Math::Vector2, Hash> closed_list;

		Node* start_node = new Node(start, 0.0, ManhattanDistance(start, end));
		open_list.push(start_node);

		std::unordered_map<Math::Vector2, Node*, Hash> all_nodes;
		all_nodes[start] = start_node;

		Node* end_node = nullptr;

		while (!open_list.empty())
		{
			Node* current_node = open_list.top();
			open_list.pop();

			if (current_node->point == end)
			{
				end_node = current_node;
				break;
			}

			if (closed_list.count(current_node->point))
				continue;
			closed_list.insert(current_node->point);

			for (const auto& neighbor_pos : GetNeighbors(current_node->point))
			{
				if (closed_list.count(neighbor_pos))
					continue;

				double tentative_g_cost = current_node->g_cost + 1.0;	 // Assume uniform cost
				if (all_nodes.find(neighbor_pos) == all_nodes.end() || tentative_g_cost < all_nodes[neighbor_pos]->g_cost)
				{
					Node* neighbor_node = new Node(neighbor_pos, tentative_g_cost, ManhattanDistance(neighbor_pos, end), current_node);
					open_list.push(neighbor_node);
					all_nodes[neighbor_pos] = neighbor_node;
				}
			}
		}

		// Reconstruct the path
		std::vector<Math::Vector2> path;
		Node* current = end_node;
		while (current != nullptr)
		{
			path.push_back(current->point);
			current = current->parent;
		}
		std::reverse(path.begin(), path.end());

		// Cleanup
		for (auto& [_, node] : all_nodes)
			delete node;

		return path;
	}

   private:
	struct Node
	{
		Math::Vector2 point;

		double g_cost;
		double h_cost;
		double f_cost() const { return g_cost + h_cost; }

		Node* parent;

		Node(Math::Vector2 point, double g, double h, Node* parent = nullptr) : point(point), g_cost(g), h_cost(h), parent(parent) {}
	};

	struct Hash
	{
		size_t operator()(const Math::Vector2& p) const
		{
			return std::hash<int>()(p.GetX()) ^ std::hash<int>()(p.GetY());
		}
	};

	std::vector<Math::Vector2> GetNeighbors(const Math::Vector2& current) 
	{
		std::vector<Math::Vector2> neighbors = {
			{current.GetX() + 1, current.GetY()},
			{current.GetX() - 1, current.GetY()},
			{current.GetX(), current.GetY() + 1},
			{current.GetX(), current.GetY() - 1},
		};

		// Filter walkable tiles
		neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [this](const Math::Vector2& pos) 
		{ 
			return !IsWalkable(pos); 
		}), neighbors.end());

		return neighbors;
	}

	//const std::vector<std::vector<int>>& grid_;
	const std::vector<Math::Vector2> directions_ = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	float ManhattanDistance(const Math::Vector2& a, const Math::Vector2& b)
	{
		return std::abs(a.GetX() - b.GetX()) + std::abs(a.GetY() - b.GetY());
	}

	bool IsWalkable(const Math::Vector2& point) const	// TODO
	{
		return true;
	}
};
