#pragma once

namespace Math
{
	class Point
	{
	public:
		Point()
			: _x{ 0 }, _y{ 0 } { }

		Point(int x, int y)
			: _x{ x }, _y{ y } { }

	private:
		int _x;
		int _y;
	};
}
