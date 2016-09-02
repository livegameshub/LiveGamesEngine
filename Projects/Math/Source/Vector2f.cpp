#include "Vector2f.h"

namespace ai
{
	Vector2f::Vector2f()
		: x(0.0f)
		, y(0.0f)
	{
	}

	Vector2f::Vector2f(f32 x, f32 y)
		: x(x)
		, y(y)
	{
	}

	Vector2f::Vector2f(f32 value)
		: x(value)
		, y(value)
	{
	}

}
