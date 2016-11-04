#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "EngineUtil.h"

#ifdef WINDOWS_BUILD
	#include <glew/glew.h>
#else 
	// we have this choice for emscripten
	#include <gl/glew.h>
#endif // WINDOWS_BUILD

namespace lg
{
	class ENGINE_API Graphics
	{
	public:
		static bool initApi();
		static void checkApiVersion();
		static void checkMaxSamples();

		static i32 getMajorApiVersion();
		static i32 getMinorApiVersion();
			   
		static i32 getMajorApiShaderVersion();
		static i32 getMinorApiShaderVersion();

	private:
		static i32 smMajorApiVersion;
		static i32 smMinorApiVersion;
			   
		static i32 smMajorApiShaderVersion;
		static i32 smMinorApiShaderVersion;
			   
		static i32 smMaxSamples;
	};
}

#endif // _GRAPHICS_H_
