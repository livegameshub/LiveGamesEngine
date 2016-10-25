#include "Time.h"

#include <glfw/glfw3.h>

namespace lg
{
	glm::f32 Time::smLastTime = 0.0f;
	glm::f32 Time::smDeltaTime = 0.0f;

	glm::f32 Time::getDeltaTime()
	{
		return smDeltaTime;
	}

	glm::f32 Time::getTimeInSeconds()
	{
		return static_cast<glm::f32>(glfwGetTime());
	}

	void Time::update()
	{
		glm::f32 new_time = getTimeInSeconds();

		smDeltaTime = new_time - smLastTime;
		smLastTime = new_time;
	}

	void Time::start()
	{
		smLastTime = getTimeInSeconds();
	}
}
