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
		
		static void keyboardKeysCallback(GLFWwindow* windowPtr, i32 key, i32 scancode, i32 action, i32 mods);
		static void mouseClicksCallback(GLFWwindow* windowPtr, i32 button, i32 action, i32 mods);
		static void mousePositionCallback(GLFWwindow* windowPtr, f64 x, f64 y);

		static bool isMousePressed(i32 button);
		static bool isKeyDown(i32 key);

		static f32 getMousePositionX();
		static f32 getMousePositionY();

		static void reset();

	private:
		static bool smKeyboardKeys[KEYBOARD_KEYS_SIZE];
		static bool smMouseClicks[MOUSE_CLICKS_SIZE];

		static f32 smMousePositionX;
		static f32 smMousePositionY;
	};
}

#endif // _INPUT_H_