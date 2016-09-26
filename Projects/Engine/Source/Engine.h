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
			STOP_FLAG = 1,
			PAUSE_FLAG = 2
		};

		void Stop();
		void Pause();
		void Resume();

		bool Setup(const std::string& title, const std::string& assetsPath);

		static const std::string& GetAssetsPath();
		static Engine& GetInstance();

		static void WindowResizeCallback(GLFWwindow* windowPtr, glm::i32 width, glm::i32 height);

	private:
		Flag mFlag;

		std::vector<Window> mWindows;
	
		Window* GetWindow(GLFWwindow* windowPtr);

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
