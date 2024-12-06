#pragma once

#include "Vector2.hpp"

namespace Math
{
	constexpr float Rad2Deg = 57.29578f;

	inline float DirectionToAngle(const Vector2& direction)
	{
		float angle = std::atan2(-direction.GetY(), direction.GetX()) * Math::Rad2Deg;
		if (angle < 0.0f)
			angle += 360.0f;

		return angle;
	}
}