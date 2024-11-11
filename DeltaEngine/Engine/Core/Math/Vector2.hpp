#pragma once

namespace Math
{
	class Vector2
	{
	public:
		Vector2()
			: _x{ 0.0f }, _y{ 0.0f } { }

		Vector2(float x, float y)
			: _x{ x }, _y{ y } { }

	private:
		float _x;
		float _y;
	};
}