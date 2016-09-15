#ifndef _MATH_UTIL_H_
#define _MATH_UTIL_H_

#include "BasicTypes.h"

/* define MATH_API */
#ifdef EXPORT_MATH_API
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

namespace ai
{
	class MATH_API Math
	{
	public:
		const f32 PI = 3.14159265f;
		const f32 EPSILON = 0.00001f;
	};
}

#endif
