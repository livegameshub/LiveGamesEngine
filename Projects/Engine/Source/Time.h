#ifndef _TIME_H_
#define _TIME_H_

#include "EngineUtil.h"

namespace ai
{
	class ENGINE_API Time
	{
	public:
		static f32 GetDeltaTime();
		static f32 GetTimeInSeconds();

		static void Update();
		static void Start();

	private:
		static f32 smDeltaTime;
		static f32 smLastTime;
	};
}

#endif
