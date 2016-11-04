#ifndef _ENGINE_UTIL_H_
#define _ENGINE_UTIL_H_

#include "Platform.h"

/* define ENGINE_API */

#ifdef WINDOWS_BUILD
	#ifdef EXPORT_ENGINE_API
		#define ENGINE_API __declspec(dllexport)
		#define EXP_TEMPLATE 
	#else
		#define ENGINE_API __declspec(dllimport)
		#define EXP_TEMPLATE extern
	#endif // EXPORT_ENGINE_API
#else 
	// if we are not on windows we should
	// replace ENGINE_API with blank space
	#define ENGINE_API 
#endif // WINDOWS_BUILD

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace std;

const string ASSETS_PATH = "Assets/";

// safe delete macro
#define SAFE_DELETE(p) { if (p) { delete (p); (p) = nullptr; } }
#define SAFE_ARRAY_DELETE(p) { if (p) { delete[] (p); (p) = nullptr; } }

/* some useful constants */
#define VECTOR_UP vec3(0.0f, 1.0f, 0.0f)
#define VECTOR_RIGHT vec3(1.0f, 0.0f, 0.0f)
#define VECTOR_FORWARD vec3(0.0f, 0.0f, -1.0f)

#endif // _ENGINE_UTIL_H_
