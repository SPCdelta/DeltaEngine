#pragma once

#include <vector>

#include "../Math/Point.hpp"

struct Node 
{
    Math::Vector2 position;

    float gCost;  // Cost from start to this node
    float hCost;  // Heuristic cost to the end
    float fCost() const { return gCost + hCost; }

    Node* parent;

    Node(const Math::Vector2& pos, float g, float h, Node* p = nullptr) : position(pos), gCost(g), hCost(h), parent(p) {}
};

struct Vector2Hash
{
	std::size_t operator()(const Math::Vector2& v) const
	{
		// Combine the x and y components to create a unique hash for each Vector2
		std::size_t h1 = std::hash<float>{}(v.GetX());
		std::size_t h2 = std::hash<float>{}(v.GetY());

		// Combine the two hashes (you can use XOR or another method)
		return h1 ^ (h2 << 1);	// Shift h2 to combine with h1
	}
};

class IAIStrategy
{
   public:
		virtual ~IAIStrategy() = default;

		virtual std::vector<Math::Vector2> CalculatePath(const Math::Vector2& start, const Math::Vector2& end) = 0;

		
};