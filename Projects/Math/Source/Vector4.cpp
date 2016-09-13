#include "Vector4.h"

namespace ai
{
	Vector4::Vector4()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{
	}

	Vector4::Vector4(f32 x, f32 y, f32 z, f32 w)
		: x(x)
		, y(y)
		, z(z)
		, w(w)
	{
	}

	Vector4::Vector4(f32 value)
		: x(value)
		, y(value)
		, z(value)
		, w(value)
	{
	}

	Vector4::Vector4(const Vector4& vector)
		: x(vector.x)
		, y(vector.y)
		, z(vector.z)
		, w(vector.w)
	{
	}
}
