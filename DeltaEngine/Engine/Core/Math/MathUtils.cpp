#include "MathUtils.hpp"

using namespace Math;

bool MathUtils::IsPointWithinRect(const Point& point, const Vector2& position, const Vector2& scale)
{
	return (point.GetX() >= position.GetX() && point.GetX() <= position.GetX() + scale.GetX()) &&
		(point.GetY() >= position.GetY() && point.GetY() <= position.GetY() + scale.GetY());
}