#ifndef _TIME_H_
#define _TIME_H_

#include "EngineUtil.h"

namespace lg
{
	class ENGINE_API Time
	{
	public:
		static f32 getDeltaTime();
		static f32 getTimeInSeconds();

		static void update();
		static void start();

	private:
		static f32 smDeltaTime;
		static f32 smLastTime;
	};
}

#endif // _TIME_H_
