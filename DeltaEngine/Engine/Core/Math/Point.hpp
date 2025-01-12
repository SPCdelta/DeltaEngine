#pragma once

namespace Math
{
	class Point
	{
	public:
		Point() = default;
		Point(int x, int y);

		int GetX() const;
		int GetY() const;

		void SetX(int x);
		void SetY(int y);
		void Set(int x, int y);

		float DistanceTo(const Point& other) const;

		bool operator==(const Point& other) const;
		bool operator!=(const Point& other) const;

	private:
		int _x;
		int _y;
	};
}