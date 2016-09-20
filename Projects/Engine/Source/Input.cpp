#include "Input.h"

#ifdef WINDOWS_BUILD
#include <glfw3.h>
#else
// we have this choice for emscripten
#include <glfw/glfw3.h>
#endif

namespace ai
{
	bool Input::smKeyboardKeys[1024];
	bool Input::smMouseClicks[10];

	f32 Input::smMousePositionX;
	f32 Input::smMousePositionY;

	void Input::KeyboardKeysCallback(GLFWwindow* windowPtr, i32 key, i32 scancode, i32 action, i32 mods)
	{
		if (action == GLFW_PRESS)
		{
			smKeyboardKeys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			smKeyboardKeys[key] = false;
		}
	}

	void Input::MouseClicksCallback(GLFWwindow* windowPtr, i32 button, i32 action, i32 mods)
	{
		if (action == GLFW_PRESS)
		{
			smMouseClicks[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			smMouseClicks[button] = false;
		}
	}

	void Input::MousePositionCallback(GLFWwindow* windowPtr, f64 x, f64 y)
	{
		smMousePositionX = static_cast<f32>(x);
		smMousePositionY = static_cast<f32>(y);
	}

	bool Input::IsMousePressed(i32 button)
	{
		return smMouseClicks[button];
	}

	bool Input::IsKeyDown(i32 key)
	{
		return smKeyboardKeys[key];
	}

	f32 Input::GetMousePositionX()
	{
		return smMousePositionX;
	}

	f32 Input::GetMousePositionY()
	{
		return smMousePositionY;
	}
}
