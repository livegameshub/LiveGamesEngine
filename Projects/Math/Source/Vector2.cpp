#include "Vector2.h"

namespace ai
{
	Vector2::Vector2()
		: x(0.0f)
		, y(0.0f)
	{
	}

	Vector2::Vector2(f32 x, f32 y)
		: x(x)
		, y(y)
	{
	}

	Vector2::Vector2(f32 value)
		: x(value)
		, y(value)
	{
	}

	Vector2::Vector2(const Vector2& vector)
		: x(vector.x)
		, y(vector.y)
	{
	}
}
