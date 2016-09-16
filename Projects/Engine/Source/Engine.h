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
		enum EngineFlag : u32
		{
			STOP_FLAG = 1,
			PAUSE_FLAG = 2
		};

		ENGINE_API void Run();
	
		ENGINE_API void Release();
		ENGINE_API void Prepare();
		ENGINE_API bool Setup(const char* title);

		ENGINE_API void Stop();
		ENGINE_API void Pause();
		ENGINE_API void Resume();

		ENGINE_API static Engine& GetInstance();

		static void WindowResizeCallback(GLFWwindow* windowPtr, i32 width, i32 height);

	private:
		Flag mFlag;

		std::vector<Window> mWindows;

		Window* GetWindow(GLFWwindow* windowPtr);
	};
}

#endif
