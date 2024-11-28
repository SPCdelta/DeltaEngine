#include <cmath>
#include "Vector2.hpp"

using namespace Math;

const Vector2 Vector2::up(0.0f, 1.0f);
const Vector2 Vector2::right(1.0f, 0.0f);

Vector2::Vector2(float x, float y) : _x{x}, _y{y} {}
Vector2::Vector2(int x, int y) : _x{ static_cast<float>(x) }, _y{ static_cast<float>(y) } {}

float Vector2::GetX() const
{
	return _x;
}

float Vector2::GetY() const
{
	return _y;
}

void Vector2::SetX(float x)
{
	_x = x;
}

void Vector2::SetY(float y)
{
	_y = y;
}

void Vector2::Set(float x, float y)
{
	_x = x;
	_y = y;
}

void Vector2::Set(const Vector2& position)
{
	_x = position.GetX();
	_y = position.GetY();
}

float Vector2::Magnitude() const
{
	return std::sqrt(_x * _x + _y * _y);
}

float Vector2::DistanceTo(const Vector2& other) const
{
	float dx = _x - other._x;
	float dy = _y - other._y;
	return std::sqrt(dx * dx + dy * dy);
}

Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta)
{
	Vector2 direction = target - current;
	float distance = direction.Magnitude();
	if (distance <= maxDistanceDelta)
	{
		return target;
	}
	direction = direction.GetNormalized() * maxDistanceDelta;
	return current + direction;
}

Vector2 Vector2::Max(const Vector2& v1, const Vector2& v2)
{
	float maxX = (v1._x > v2._x) ? v1._x : v2._x;
	float maxY = (v1._y > v2._y) ? v1._y : v2._y;
	return Vector2(maxX, maxY);
}

Vector2 Vector2::Min(const Vector2& v1, const Vector2& v2)
{
	float minX = (v1._x < v2._x) ? v1._x : v2._x;
	float minY = (v1._y < v2._y) ? v1._y : v2._y;
	return Vector2(minX, minY);
}

bool Vector2::IsPointWithinRect(const Point& point, const Vector2& position, const Vector2& scale)
{
	return (point.GetX() >= position.GetX() && point.GetX() <= position.GetX() + scale.GetX()) &&
		(point.GetY() >= position.GetY() && point.GetY() <= position.GetY() + scale.GetY());
}

Vector2 Vector2::GetNormalized() const
{
	float len = Magnitude();
	if (len != 0)
	{
		return Vector2(_x / len, _y / len);
	}
	return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(_x + other._x, _y + other._y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(_x - other._x, _y - other._y);
}

Vector2 Vector2::operator-(float other) const
{
	return Vector2(_x - other, _y - other);
}

Vector2 Math::Vector2::operator-() const
{
	return Vector2(-_x, -_y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(_x * scalar, _y * scalar);
}

bool Vector2::operator==(const Vector2& other) const
{
	return _x == other._x && _y == other._y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

bool Vector2::IsNonZero() const
{
	return _x != 0 && _y != 0;
}
