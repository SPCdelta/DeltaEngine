#include <cmath>
#include "Point.hpp"

using namespace Math;

Point::Point(float x, float y) : _x{x}, _y{y} {}

Point::Point(int x, int y) : _x{static_cast<float>(x)}, _y{static_cast<float>(y)} {}

float Point::GetX() const
{
	return _x;
}

float Point::GetY() const
{
	return _y;
}

void Point::SetX(float x)
{
	_x = x;
}

void Point::SetY(float y)
{
	_y = y;
}

void Point::Set(float x, float y)
{
	_x = x;
	_y = y;
}

float Point::DistanceTo(const Point& other) const
{
	float dx = _x - other._x;
	float dy = _y - other._y;
	return std::sqrt(dx * dx + dy * dy);
}

bool Point::operator==(const Point& other) const
{
	return _x == other._x && _y == other._y;
}

bool Point::operator != (const Point& other) const
{
	return !(*this == other);
}
