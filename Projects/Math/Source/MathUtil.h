#ifndef _MATH_UTIL_H_
#define _MATH_UTIL_H_

#include "BasicTypes.h"

#ifdef WINDOWS_BUILD
/* define MATH_API */
	#ifdef EXPORT_MATH_API
		#define MATH_API __declspec(dllexport)
	#else
		#define MATH_API __declspec(dllimport)
	#endif
#else
	// if we are not on windows we should
	// replace MATH_API with blank space
	#define MATH_API 
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
