#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "EngineUtil.h"

#ifdef WINDOWS_BUILD
	#include <glew/glew.h>
#else 
	// we have this choice for emscripten
	#include <gl/glew.h>
#endif

namespace ai
{
	class ENGINE_API Graphics
	{
	public:
		static bool initApi();
		static void checkApiVersion();
		static void checkMaxSamples();

		static glm::i32 getMajorApiVersion();
		static glm::i32 getMinorApiVersion();
			   
		static glm::i32 getMajorApiShaderVersion();
		static glm::i32 getMinorApiShaderVersion();

	private:
		static glm::i32 smMajorApiVersion;
		static glm::i32 smMinorApiVersion;
			   
		static glm::i32 smMajorApiShaderVersion;
		static glm::i32 smMinorApiShaderVersion;
			   
		static glm::i32 smMaxSamples;
	};
}

#endif
