#ifndef _MATRIX_4_H_
#define _MATRIX_4_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Matrix4
	{
		Matrix4();
		Matrix4(const f32 data[16]);

		/* members */

		f32 data[16];
	};
}

#endif
