#ifndef _INPUT_H_
#define _INPUT_H_

#include "EngineUtil.h"

struct GLFWwindow;

namespace ai
{
	class ENGINE_API Input
	{
	public:
		static void KeyboardKeysCallback(GLFWwindow* windowPtr, glm::i32 key, glm::i32 scancode, glm::i32 action, glm::i32 mods);
		static void MouseClicksCallback(GLFWwindow* windowPtr, glm::i32 button, glm::i32 action, glm::i32 mods);
		static void MousePositionCallback(GLFWwindow* windowPtr, glm::f64 x, glm::f64 y);

		static bool IsMousePressed(glm::i32 button);
		static bool IsKeyDown(glm::i32 key);

		static glm::f32 GetMousePositionX();
		static glm::f32 GetMousePositionY();

	private:
		static bool smKeyboardKeys[1024];
		static bool smMouseClicks[10];

		static glm::f32 smMousePositionX;
		static glm::f32 smMousePositionY;
	};
}

#endif