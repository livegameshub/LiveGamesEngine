#include "Time.h"

#include <glfw3.h>

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
