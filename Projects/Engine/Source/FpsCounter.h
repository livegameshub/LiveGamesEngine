#ifdef _DEBUG
#ifndef _FPS_COUNTER_H_
#define _FPS_COUNTER_H_

#include "EngineUtil.h"

namespace ai
{
	class FpsCounter
	{
	public:
		static void update();

	private:
		static glm::f32 smFramesTime;
		static glm::u32 smFrames;
	};
}

#endif // _FPS_COUNTER_H_
#endif // _DEBUG
