#include "Vector4f.h"

namespace ai
{
	Vector4f::Vector4f()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{
	}

	Vector4f::Vector4f(f32 x, f32 y, f32 z, f32 w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
	}

	Vector4f::Vector4f(f32 value)
		: x(value)
		, y(value)
		, z(value)
		, w(value)
	{
	}
}
