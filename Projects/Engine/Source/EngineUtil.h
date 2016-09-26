#ifndef _ENGINE_UTIL_H_
#define _ENGINE_UTIL_H_

/* define ENGINE_API */
#ifdef WINDOWS_BUILD
	#ifdef EXPORT_ENGINE_API
		#define ENGINE_API __declspec(dllexport)
		#define EXP_TEMPLATE 
	#else
		#define ENGINE_API __declspec(dllimport)
		#define EXP_TEMPLATE extern
	#endif
#else 
	// if we are not on windows we should
	// replace ENGINE_API with blank space
	#define ENGINE_API 
#endif

#include "Platform.h"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#endif
