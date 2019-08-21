#pragma once

#define PI 3.14159265358979323846
#include <cmath>

namespace astro { namespace math {

	struct Vector2f
	{
		float x, y;
		
		Vector2f();
		Vector2f(const float& x, const float& y);
		Vector2f(const Vector2f& other);
		Vector2f(const float& angle);

		inline Vector2f operator+(const Vector2f& other) const
		{
			return Vector2f(x + other.x, y + other.y);
		}

		inline Vector2f operator-(const Vector2f& other) const
		{
			return Vector2f(x - other.x, y - other.y);
		}

		inline Vector2f operator*(const float& scalar) const
		{
			return Vector2f(x * scalar, y * scalar);
		}

		inline Vector2f operator/(const float& scalar) const
		{
			float oneOverScalar = 1.0f / scalar;
			return Vector2f(x * oneOverScalar, y * oneOverScalar);
		}

		inline Vector2f& operator+=(const Vector2f& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		inline Vector2f& operator-=(const Vector2f& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vector2f& operator*=(const float& scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vector2f& operator/=(const float& scalar)
		{
			float oneOverScalar = 1.0f / scalar;
			x *= oneOverScalar;
			y *= oneOverScalar;
			return *this;
		}

		void Normalize();
		
		inline float Length() { return (float)sqrt(x * x + y * y); }
		inline float Angle()  { return (float)atan2(y, x);	}
		
		inline const float DistanceSq(const Vector2f& other)
		{
			float dx = x - other.x;
			float dy = y - other.y;
			return dx * dx + dy * dy;
		}

		inline float Distance(const Vector2f &other) { return sqrtf(DistanceSq(other)); }
	};

} }