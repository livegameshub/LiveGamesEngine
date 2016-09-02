#ifndef _VECTOR_2F_H_
#define _VECTOR_2F_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Vector2f
	{
		Vector2f();
		Vector2f(f32 x, f32 y);
		Vector2f(f32 value);

		f32 x;
		f32 y;
	};
}

#endif
