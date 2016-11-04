#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "EngineUtil.h"

namespace lg
{
	struct ENGINE_API Random
	{
		static u32 getRandomInt(u32 max);
		static u32 getRandomInt(u32 min, u32 max);
		static f32 getRandomFloat(f32 min, f32 max);

		static void seed();
	};
}

#endif // _RANDOM_H_
