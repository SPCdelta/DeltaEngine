#pragma once

namespace Math
{
	class Vector2
	{
	public:
		static const Math::Vector2 up;
		static const Math::Vector2 right;

		Vector2() = default;
		Vector2(float x, float y);
		float GetX() const;
		float GetY() const;
		void SetX(float x);
		void SetY(float y);
		void Set(float x, float y);
		void Set(const Vector2& position);
		// AKA length
		float Magnitude() const;
		float DistanceTo(const Vector2& other) const;
		Vector2 GetNormalized() const;
		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator-() const;
		Vector2 operator*(float scalar) const;
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		// Moves a point current towards target.
		static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);
		static Vector2 Max(const Vector2& v1, const Vector2& v2);
		static Vector2 Min(const Vector2& v1, const Vector2& v2);
	private:
		float _x;
		float _y;
	};
}