#include "Vector3.h"

namespace ai
{
	Vector3::Vector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{
	}

	Vector3::Vector3(f32 x, f32 y, f32 z)
		: x(x)
		, y(y)
		, z(z)
	{
	}

	Vector3::Vector3(f32 value)
		: x(value)
		, y(value)
		, z(value)
	{
	}

	Vector3::Vector3(const Vector3& vector)
		: x(vector.x)
		, y(vector.y)
		, z(vector.z)
	{
	}
}
