#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Window.h"
#include "Flag.h"

struct GLFWwindow;

namespace ai
{
	class ENGINE_API Engine
	{
	public:
		enum EngineFlag : u32
		{
			STOP_FLAG = 1,
			PAUSE_FLAG = 2
		};

		void Stop();
		void Pause();
		void Resume();

		bool Setup(const char* title);

		static Engine& GetInstance();

		static void WindowResizeCallback(GLFWwindow* windowPtr, i32 width, i32 height);

	private:
		Flag mFlag;

		std::vector<Window> mWindows;

		Window* GetWindow(GLFWwindow* windowPtr);

		void Release();
		void Prepare();
		void Run();
	};
}

#endif
