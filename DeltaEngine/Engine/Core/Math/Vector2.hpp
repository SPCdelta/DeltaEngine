#pragma once

#include "Point.hpp"

namespace Math
{
	class Vector2
	{
	public:
		static const Math::Vector2 up;
		static const Math::Vector2 right;

		Vector2() = default;
		Vector2(float x, float y);
		Vector2(int x, int y);
		float GetX() const;
		float GetY() const;
		void SetX(float x);
		void SetY(float y);
		void Set(float x, float y);
		void Set(const Vector2& position);
		void AddX(float x);
		void AddY(float y);
		Vector2 AddX(float x) const;
		Vector2 AddY(float y) const;
		// AKA length
		float Magnitude() const;
		float DistanceTo(const Vector2& other) const;
		Math::Vector2 DirectionTo(const Vector2& other) const;
		Vector2 GetNormalized() const;
		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;
		Vector2 operator-(float other) const;
		Vector2 operator-() const;
		Vector2 operator*(float scalar) const;
		Vector2& operator+=(const Vector2& other);
		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;
		bool IsNonZero() const;
		// Moves a point current towards target.
		static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);
		static Vector2 Max(const Vector2& v1, const Vector2& v2);
		static Vector2 Min(const Vector2& v1, const Vector2& v2);
	private:
		float _x = 0.0f;
		float _y = 0.0f;
	};
}