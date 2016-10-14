#include "Input.h"

namespace ai
{
	bool Input::smKeyboardKeys[1024];
	bool Input::smMouseClicks[10];

	glm::f32 Input::smMousePositionX;
	glm::f32 Input::smMousePositionY;

	void Input::keyboardKeysCallback(GLFWwindow* windowPtr, glm::i32 key, glm::i32 scancode, glm::i32 action, glm::i32 mods)
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

	void Input::mouseClicksCallback(GLFWwindow* windowPtr, glm::i32 button, glm::i32 action, glm::i32 mods)
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

	void Input::mousePositionCallback(GLFWwindow* windowPtr, glm::f64 x, glm::f64 y)
	{
		smMousePositionX = static_cast<glm::f32>(x);
		smMousePositionY = static_cast<glm::f32>(y);
	}

	bool Input::isMousePressed(glm::i32 button)
	{
		return smMouseClicks[button];
	}

	bool Input::isKeyDown(glm::i32 key)
	{
		return smKeyboardKeys[key];
	}

	glm::f32 Input::getMousePositionX()
	{
		return smMousePositionX;
	}

	glm::f32 Input::getMousePositionY()
	{
		return smMousePositionY;
	}
}
