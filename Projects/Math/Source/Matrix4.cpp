#include "Matrix4.h"
#include <cstring>

namespace ai
{
	Matrix4::Matrix4()
	{
		std::memset(data, 0, 16);

		data[0] = data[5] = data[10] = data[15] = 1.0f;
	}

	Matrix4::Matrix4(const f32 data[16])
	{
		std::memcpy(this->data, data, 16);
	}
}
