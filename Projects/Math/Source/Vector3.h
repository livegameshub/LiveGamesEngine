#ifndef _VECTOR_3_H_
#define _VECTOR_3_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Vector3
	{
		Vector3();
		Vector3(f32 x, f32 y, f32 z);
		Vector3(f32 value);

		Vector3(const Vector3& vector);
		Vector3& operator=(const Vector3& vector);

		f32 x;
		f32 y;
		f32 z;
	};
}

#endif
