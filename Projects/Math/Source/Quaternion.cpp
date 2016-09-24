#include "Quaternion.h"

namespace ai
{
	Quaternion::Quaternion()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(1.0f)
	{
	}

	void Quaternion::Identity()
	{
		x = y = z = 0.0f;

		w = 1.0f;
	}
}
