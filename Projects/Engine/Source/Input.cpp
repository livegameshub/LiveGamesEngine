#include "Input.h"

namespace lg
{
	bool Input::smKeyboardKeys[KEYBOARD_KEYS_SIZE];
	bool Input::smMouseClicks[MOUSE_CLICKS_SIZE];

	f32 Input::smMousePositionX;
	f32 Input::smMousePositionY;

	void Input::keyboardKeysCallback(GLFWwindow* windowPtr, i32 key, i32 scancode, i32 action, i32 mods)
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

	void Input::mouseClicksCallback(GLFWwindow* windowPtr, i32 button, i32 action, i32 mods)
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

	void Input::mousePositionCallback(GLFWwindow* windowPtr, f64 x, f64 y)
	{
		smMousePositionX = static_cast<f32>(x);
		smMousePositionY = static_cast<f32>(y);
	}

	bool Input::isMousePressed(i32 button)
	{
		return smMouseClicks[button];
	}

	bool Input::isKeyDown(i32 key)
	{
		return smKeyboardKeys[key];
	}

	f32 Input::getMousePositionX()
	{
		return smMousePositionX;
	}

	f32 Input::getMousePositionY()
	{
		return smMousePositionY;
	}

	void Input::reset()
	{
		// TODO
		// memset ??
		for (int i = 0; i < KEYBOARD_KEYS_SIZE; ++i)
		{
			smKeyboardKeys[i] = false;
		}

		for (int i = 0; i < MOUSE_CLICKS_SIZE; ++i)
		{
			smMouseClicks[i] = false;
		}
	}
}
