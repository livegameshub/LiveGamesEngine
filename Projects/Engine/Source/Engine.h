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
		static bool Setup(const std::string& mainWindowTitle, const std::string& assetsPath);
		static void WindowResizeCallback(GLFWwindow* windowPtr, glm::i32 width, glm::i32 height);

		static const std::string& GetAssetsPath();
		static Engine& GetInstance();

		Window* GetWindow(GLFWwindow* windowPtr);
		Window* GetWindowByIndex(glm::u32 index);

	private:
		Flag mFlag;

		std::vector<Window> mWindows;

		#ifndef WINDOWS_BUILD
		static void WebLoop();
		#endif

		static std::string smAssetsPath;

		void Release();
		void Prepare();
		void Loop();
		void Run();
	};
}

#endif
