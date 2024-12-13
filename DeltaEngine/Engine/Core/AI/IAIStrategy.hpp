#pragma once

#include <vector>
#include <string>

#include "../Math/Point.hpp"
#include "../Math/Vector2.hpp"

struct Node 
{
    Math::Vector2 position;
	std::string tag;

    Node* parent;

    Node(const Math::Vector2& pos, Node* p = nullptr) : position(pos), parent(p) {}
};

struct Vector2Hash
{
	std::size_t operator()(const Math::Vector2& v) const
	{
		// Combine the x and y to create a unique hash for each Vector2
		std::size_t h1 = std::hash<float>{}(v.GetX());
		std::size_t h2 = std::hash<float>{}(v.GetY());

		// Combine the two hashes 
		return h1 ^ (h2 << 1);
	}
};

class IAIStrategy
{
   public:
		virtual ~IAIStrategy() = default;

		// Range is amount of units in each direction, with step being 1 node per step amount of units
		virtual std::vector<Math::Vector2> CalculatePath(Math::Vector2& start, Math::Vector2& end, int range = 500, int step = 50) = 0; 
};