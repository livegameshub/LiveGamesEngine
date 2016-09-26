#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "EngineUtil.h"

#ifdef WINDOWS_BUILD
#include <glew.h>
#else 
// we have this choice for emscripten
#include <gl/glew.h>
#endif

namespace ai
{
	class ENGINE_API Graphics
	{
	public:
		static bool InitApi();
		static void CheckApiVersion();
		static void CheckMaxSamples();

		static glm::i32 GetMajorApiVersion();
		static glm::i32 GetMinorApiVersion();
			   
		static glm::i32 GetMajorApiShaderVersion();
		static glm::i32 GetMinorApiShaderVersion();

	private:
		static glm::i32 smMajorApiVersion;
		static glm::i32 smMinorApiVersion;
			   
		static glm::i32 smMajorApiShaderVersion;
		static glm::i32 smMinorApiShaderVersion;
			   
		static glm::i32 smMaxSamples;
	};
}

#endif
