#ifdef _DEBUG
#ifndef _FPS_COUNTER_H_
#define _FPS_COUNTER_H_

#include "EngineUtil.h"

namespace lg
{
	class FpsCounter
	{
	public:
		static void update();

	private:
		static f32 smFramesTime;
		static u32 smFrames;
	};
}

#endif // _FPS_COUNTER_H_
#endif // _DEBUG
