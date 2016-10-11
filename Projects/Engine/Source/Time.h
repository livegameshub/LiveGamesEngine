#ifndef _TIME_H_
#define _TIME_H_

#include "EngineUtil.h"

namespace ai
{
	class ENGINE_API Time
	{
	public:
		static glm::f32 getDeltaTime();
		static glm::f32 getTimeInSeconds();

		static void update();
		static void start();

	private:
		static glm::f32 smDeltaTime;
		static glm::f32 smLastTime;
	};
}

#endif
