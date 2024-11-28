#pragma once

#include "Point.hpp"
#include "Vector2.hpp"

namespace Math
{
class MathUtils
{
   public:
	static bool IsPointWithinRect(const Point& point, const Vector2& position,
								  const Vector2& scale);
};
}  // namespace Math
