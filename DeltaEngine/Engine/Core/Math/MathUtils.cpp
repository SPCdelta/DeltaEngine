#include "MathUtils.hpp"

using namespace Math;

bool MathUtils::IsPointWithinRect(const Point& point, const Vector2& position, const Vector2& scale)
{
	return (point.GetX() >= position.GetX() && point.GetX() <= position.GetX() + scale.GetX()) &&
		(point.GetY() >= position.GetY() && point.GetY() <= position.GetY() + scale.GetY());
}

bool MathUtils::IsVector2WithinRect(const Vector2& floatPoint, const Vector2& position, const Vector2& scale)
{
	return (floatPoint.GetX() >= position.GetX() && floatPoint.GetX() <= position.GetX() + scale.GetX()) &&
		(floatPoint.GetY() >= position.GetY() && floatPoint.GetY() <= position.GetY() + scale.GetY());
}