#ifndef _INPUT_H_
#define _INPUT_H_

#include "EngineUtil.h"

#include <glfw/glfw3.h>

struct GLFWwindow;

namespace ai
{
	class ENGINE_API Input
	{
	public:
		static void keyboardKeysCallback(GLFWwindow* windowPtr, glm::i32 key, glm::i32 scancode, glm::i32 action, glm::i32 mods);
		static void mouseClicksCallback(GLFWwindow* windowPtr, glm::i32 button, glm::i32 action, glm::i32 mods);
		static void mousePositionCallback(GLFWwindow* windowPtr, glm::f64 x, glm::f64 y);

		static bool isMousePressed(glm::i32 button);
		static bool isKeyDown(glm::i32 key);

		static glm::f32 getMousePositionX();
		static glm::f32 getMousePositionY();

	private:
		static bool smKeyboardKeys[1024];
		static bool smMouseClicks[10];

		static glm::f32 smMousePositionX;
		static glm::f32 smMousePositionY;
	};
}

#endif // _INPUT_H_