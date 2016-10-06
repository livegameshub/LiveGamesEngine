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
		enum EngineFlag : glm::u32
		{
			ENGINE_STOP_FLAG = 1,
			ENGINE_PAUSE_FLAG = 2
		};

		void Stop();
		void Pause();
		void Resume();

		void AddWindow(const Window& window);

		// TODO
		// setup should return an int with some specific codes
		static bool Setup(const std::string& mainWindowTitle);
		static void WindowResizeCallback(GLFWwindow* windowPtr, glm::i32 width, glm::i32 height);

		Window* GetWindow(GLFWwindow* windowPtr);
		Window* GetWindowByIndex(glm::u32 index);

		static Engine& getInstance();

	private:
		Flag mFlag;

		std::vector<Window> mWindows;

		static void Release();

		#ifndef WINDOWS_BUILD
		static void WebLoop();
		#endif

		void Prepare();
		void Loop();
		void Run();
	};
}

#endif
