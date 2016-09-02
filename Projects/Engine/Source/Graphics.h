#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "EngineUtil.h"

#include <glew.h>

namespace ai
{
	class ENGINE_API Graphics
	{
	public:
		static bool InitApi();
		static void CheckApiVersion();
		static void CheckMaxSamples();

		static i32 GetMajorApiVersion();
		static i32 GetMinorApiVersion();
			   
		static i32 GetMajorApiShaderVersion();
		static i32 GetMinorApiShaderVersion();

	private:
		static i32 smMajorApiVersion;
		static i32 smMinorApiVersion;
			   
		static i32 smMajorApiShaderVersion;
		static i32 smMinorApiShaderVersion;
			   
		static i32 smMaxSamples;
	};
}

#endif
