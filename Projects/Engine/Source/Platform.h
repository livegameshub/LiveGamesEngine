#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/* define ENGINE_API */
#ifdef EXPORT_ENGINE_API
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

/* includes */
#include <cstdint>
#include <stdlib.h>
#include <time.h>

#include <string>
#include <fstream>
#include <sstream>

#include <vector>
#include <map>

/* debug includes */
#ifdef _DEBUG
#include <iostream>
#endif

namespace ai
{
	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;

	typedef int8_t i8;
	typedef int16_t i16;
	typedef int32_t i32;

	typedef float_t f32;
	typedef double_t f64;
}

#endif