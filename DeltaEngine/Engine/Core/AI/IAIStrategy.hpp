#pragma once

#include <vector>

#include "../Math/Point.hpp"

class IAIStrategy
{
   public:
		virtual ~IAIStrategy() = default;

		virtual std::vector<Math::Vector2> CalculatePath(const Math::Vector2& start, const Math::Vector2& end) = 0;
};