#ifndef _ENGINE_UTIL_H_
#define _ENGINE_UTIL_H_

/* define ENGINE_API */
#ifdef EXPORT_ENGINE_API
#define ENGINE_API __declspec(dllexport)
#define EXP_TEMPLATE 
#else
#define ENGINE_API __declspec(dllimport)
#define EXP_TEMPLATE extern
#endif

#include "Platform.h"

/* define the basic types */
#include "BasicTypes.h"

#endif
