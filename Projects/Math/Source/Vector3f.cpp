#include "Vector3f.h"

namespace ai
{
	Vector3f::Vector3f()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{
	}

	Vector3f::Vector3f(f32 x, f32 y, f32 z)
		: x(x)
		, y(y)
		, z(z)
	{
	}

	Vector3f::Vector3f(f32 value)
		: x(value)
		, y(value)
		, z(value)
	{
	}
}
