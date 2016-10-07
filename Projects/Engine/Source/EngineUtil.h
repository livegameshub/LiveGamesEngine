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
	#endif
#else 
	// if we are not on windows we should
	// replace ENGINE_API with blank space
	#define ENGINE_API 
#endif

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/* some useful constants */
const glm::vec3 VECTOR_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 VECTOR_RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 VECTOR_FORWARD = glm::vec3(0.0f, 0.0f, -1.0f);

const std::string ASSETS_PATH = "Assets/";

#endif
