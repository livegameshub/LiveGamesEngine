#ifndef _VECTOR_4_H_
#define _VECTOR_4_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Vector4
	{
		Vector4();
		Vector4(f32 x, f32 y, f32 z, f32 w);
		Vector4(f32 value);

		Vector4(const Vector4& vector);

		f32 x;
		f32 y;
		f32 z;
		f32 w;
	};
}

#endif
