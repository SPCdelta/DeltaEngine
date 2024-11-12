#pragma once

namespace Math
{
	class Vector2
	{
	public:
		Vector2()
			: x{ 0.0f }, y{ 0.0f } { }

		Vector2(float x, float y)
			: x{ x }, y{ y } { }

		float x;
		float y;
	};
}