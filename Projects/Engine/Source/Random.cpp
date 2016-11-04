#include "Random.h"

#include "glm/gtc/random.hpp"

#include <time.h>

namespace lg
{
	void Random::seed()
	{
		srand(static_cast<u32>(time(0)));
	}

	u32 Random::getRandomInt(u32 max)
	{
		return rand() % (max + 1);
	}

	u32 Random::getRandomInt(u32 min, u32 max)
	{
		return rand() % (max - min + 1) + min;
	}

	f32 Random::getRandomFloat(f32 min, f32 max)
	{
		return linearRand(min, max);
	}
}
