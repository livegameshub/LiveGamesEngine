#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Window.h"
#include "Flag.h"

struct GLFWwindow;

namespace ai
{
	class Engine
	{
	public:
		ENGINE_API void Run();
		ENGINE_API void Stop();

		ENGINE_API void Prepare();
		ENGINE_API bool Setup(const char* title);

		ENGINE_API static Engine& GetInstance();

		static void WindowResizeCallback(GLFWwindow* windowPtr, i32 width, i32 height);

	private:
		Engine();

		bool mIsStoped;

		std::vector<Window> mWindows;

		Window* GetWindow(GLFWwindow* windowPtr);
	};
}

#endif
