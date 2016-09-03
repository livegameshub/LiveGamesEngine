#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Window.h"

struct GLFWwindow;

namespace ai
{
	class Engine
	{
	public:
		ENGINE_API void Run();
		ENGINE_API bool Setup(const char* title);

		ENGINE_API static Engine& GetInstance();

		static void WindowResizeCallback(GLFWwindow* window, i32 width, i32 height);

	private:
		std::vector<Window> mWindows;
	};
}

#endif
