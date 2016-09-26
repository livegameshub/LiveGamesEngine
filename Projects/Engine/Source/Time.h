#ifndef _TIME_H_
#define _TIME_H_

#include "EngineUtil.h"

namespace ai
{
	class ENGINE_API Time
	{
	public:
		static glm::f32 GetDeltaTime();
		static glm::f32 GetTimeInSeconds();

		static void Update();
		static void Start();

	private:
		static glm::f32 smDeltaTime;
		static glm::f32 smLastTime;
	};
}

#endif
