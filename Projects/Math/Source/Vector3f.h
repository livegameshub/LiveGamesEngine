#ifndef _VECTOR_3F_H_
#define _VECTOR_3F_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Vector3f
	{
		Vector3f();
		Vector3f(f32 x, f32 y, f32 z);
		Vector3f(f32 value);

		f32 x;
		f32 y;
		f32 z;
	};
}

#endif
