#ifndef _VECTOR_4F_H_
#define _VECTOR_4F_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Vector4f
	{
		Vector4f();
		Vector4f(f32 x, f32 y, f32 z, f32 w);
		Vector4f(f32 value);

		f32 x;
		f32 y;
		f32 z;
		f32 w;
	};
}

#endif
