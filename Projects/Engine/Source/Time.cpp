#include "Time.h"

#ifdef WINDOWS_BUILD
	#include <glfw3.h>
#else
	// we have this choice for emscripten
	#include <glfw/glfw3.h>
#endif

namespace ai
{
	glm::f32 Time::smLastTime = 0.0f;
	glm::f32 Time::smDeltaTime = 0.0f;

	glm::f32 Time::GetDeltaTime()
	{
		return smDeltaTime;
	}

	glm::f32 Time::GetTimeInSeconds()
	{
		return static_cast<glm::f32>(glfwGetTime());
	}

	void Time::Update()
	{
		glm::f32 new_time = GetTimeInSeconds();

		smDeltaTime = new_time - smLastTime;
		smLastTime = new_time;
	}

	void Time::Start()
	{
		smLastTime = GetTimeInSeconds();
	}
}
