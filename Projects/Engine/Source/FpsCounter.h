#ifdef _DEBUG
#ifndef _FPS_COUNTER_H_
#define _FPS_COUNTER_H_

#include "EngineUtil.h"

namespace ai
{
	class FpsCounter
	{
	public:
		static void Update();

	private:
		static f32 smFramesTime;
		static u32 smFrames;
	};
}

#endif
#endif
