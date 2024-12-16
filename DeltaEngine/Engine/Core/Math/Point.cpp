#include <cmath>
#include "Point.hpp"

using namespace Math;

Point::Point(int x, int y) : _x{ x }, _y{ y } {}

int Point::GetX() const
{
	return _x;
}

int Point::GetY() const
{
	return _y;
}

void Point::SetX(int x)
{
	_x = x;
}

void Point::SetY(int y)
{
	_y = y;
}

void Point::Set(int x, int y)
{
	_x = x;
	_y = y;
}

float Point::DistanceTo(const Point& other) const
{
	int dx = _x - other._x;
	int dy = _y - other._y;
	return static_cast<float>(std::sqrt(dx * dx + dy * dy));
}

bool Point::operator==(const Point& other) const
{
	return _x == other._x && _y == other._y;
}

bool Point::operator != (const Point& other) const
{
	return !(*this == other);
}