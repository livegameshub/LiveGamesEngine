#ifndef _INPUT_H_
#define _INPUT_H_

#include "EngineUtil.h"

#include <glfw/glfw3.h>

struct GLFWwindow;

namespace lg
{
	class ENGINE_API Input
	{
	public:
		static const int MOUSE_CLICKS_SIZE = 10;
		static const int KEYBOARD_KEYS_SIZE = 1024;
		
		static void keyboardKeysCallback(GLFWwindow* windowPtr, glm::i32 key, glm::i32 scancode, glm::i32 action, glm::i32 mods);
		static void mouseClicksCallback(GLFWwindow* windowPtr, glm::i32 button, glm::i32 action, glm::i32 mods);
		static void mousePositionCallback(GLFWwindow* windowPtr, glm::f64 x, glm::f64 y);

		static bool isMousePressed(glm::i32 button);
		static bool isKeyDown(glm::i32 key);

		static glm::f32 getMousePositionX();
		static glm::f32 getMousePositionY();

		static void reset();

	private:
		static bool smKeyboardKeys[KEYBOARD_KEYS_SIZE];
		static bool smMouseClicks[MOUSE_CLICKS_SIZE];

		static glm::f32 smMousePositionX;
		static glm::f32 smMousePositionY;
	};
}

#endif // _INPUT_H_