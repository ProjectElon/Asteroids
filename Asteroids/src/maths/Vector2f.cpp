#include "Vector2f.h"

namespace astro { namespace math {

	Vector2f::Vector2f()
		: x(0.0f), y(0.0f)
	{
	}

	Vector2f::Vector2f(const float& x, const float& y) 
		: x(x), y(y)
	{
	}

	Vector2f::Vector2f(const Vector2f& other)
		: x(other.x), y(other.y)
	{
	}

	Vector2f::Vector2f(const float& angle)
		: x((float)(1*cos(angle * PI / 180.0f))), y((float)(1*sin(angle * PI / 180.0f)))
	{
	}


	void Vector2f::Normalize()
	{
		float len = Length();
		
		if (len != 0)
		{
			x /= len;
			y /= len;
		}
	}

} }