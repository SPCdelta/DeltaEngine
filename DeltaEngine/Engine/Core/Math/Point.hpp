#pragma once

namespace Math
{
	class Point
	{
	public:
		Point() = default;
		Point(float x, float y);
		Point(int x, int y);
		float GetX() const;
		float GetY() const;
		void SetX(float x);
		void SetY(float y);
		void Set(float x, float y);
		float DistanceTo(const Point& other) const;
		bool operator==(const Point& other) const;
		bool operator!=(const Point& other) const;
	private:
		float _x;
		float _y;
	};
}
