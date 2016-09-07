#ifndef _INPUT_H_
#define _INPUT_H_

#include "EngineUtil.h"

struct GLFWwindow;

namespace ai
{
	class ENGINE_API Input
	{
	public:
		static void KeyboardKeysCallback(GLFWwindow* windowPtr, i32 key, i32 scancode, i32 action, i32 mods);
		static void MouseClicksCallback(GLFWwindow* windowPtr, i32 button, i32 action, i32 mods);
		static void MousePositionCallback(GLFWwindow* windowPtr, f64 x, f64 y);

		static bool IsMousePressed(i32 button);
		static bool IsKeyDown(i32 key);

		static f32 GetMousePositionX();
		static f32 GetMousePositionY();

	private:
		static bool smKeyboardKeys[1024];
		static bool smMouseClicks[10];

		static f32 smMousePositionX;
		static f32 smMousePositionY;
	};
}

#endif