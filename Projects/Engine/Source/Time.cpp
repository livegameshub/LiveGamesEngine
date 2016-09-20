#include "Time.h"

#ifdef WINDOWS_BUILD
#include <glfw3.h>
#else
// we have this choice for emscripten
#include <glfw/glfw3.h>
#endif

namespace ai
{
	f32 Time::smLastTime = 0.0f;
	f32 Time::smDeltaTime = 0.0f;

	f32 Time::GetDeltaTime()
	{
		return smDeltaTime;
	}

	f32 Time::GetTimeInSeconds()
	{
		return static_cast<f32>(glfwGetTime());
	}

	void Time::Update()
	{
		f32 new_time = GetTimeInSeconds();

		smDeltaTime = new_time - smLastTime;
		smLastTime = new_time;
	}

	void Time::Start()
	{
		smLastTime = GetTimeInSeconds();
	}
}
