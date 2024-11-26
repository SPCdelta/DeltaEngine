#include <cmath>
#include "Vector2.hpp"

using namespace Math;

const Math::Vector2 Math::Vector2::up(0.0f, 1.0f);
const Math::Vector2 Math::Vector2::right(1.0f, 0.0f);

Vector2::Vector2(float x, float y) : _x{x}, _y{y} {}

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
