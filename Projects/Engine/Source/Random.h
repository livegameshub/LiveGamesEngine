#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "EngineUtil.h"

namespace ai
{
	struct ENGINE_API Random
	{
		static glm::u32 getRandomInt(glm::u32 max);
		static glm::u32 getRandomInt(glm::u32 min, glm::u32 max);
		static glm::f32 getRandomFloat(glm::f32 min, glm::f32 max);

		static void seed();
	};
}

#endif
