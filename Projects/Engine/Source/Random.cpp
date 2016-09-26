#include "Random.h"

#include "glm/gtc/random.hpp"

#include <time.h>

namespace ai
{
	void Random::Seed()
	{
		srand(static_cast<glm::u32>(time(0)));
	}

	glm::u32 Random::GetRandomInt(glm::u32 max)
	{
		return rand() % (max + 1);
	}

	glm::u32 Random::GetRandomInt(glm::u32 min, glm::u32 max)
	{
		return rand() % (max - min + 1) + min;
	}

	glm::f32 Random::GetRandomFloat(glm::f32 min, glm::f32 max)
	{
		return glm::linearRand(min, max);
	}
}
