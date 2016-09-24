#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "MathUtil.h"

namespace ai
{
	struct MATH_API Quaternion
	{
		Quaternion();

		/* members */

		f32 x;
		f32 y;
		f32 z;
		f32 w;
	};
}

#endif
