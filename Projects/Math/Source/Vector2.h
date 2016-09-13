#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Vector2
	{
		Vector2();
		Vector2(f32 x, f32 y);
		Vector2(f32 value);

		Vector2(const Vector2& vector);

		f32 x;
		f32 y;
	};
}

#endif
