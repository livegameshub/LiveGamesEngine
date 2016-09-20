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

		bool Setup(const std::string& title, const std::string& assetsPath);

		static Engine& GetInstance();
		static const std::string& GetAssetsPath();

		static void WindowResizeCallback(GLFWwindow* windowPtr, i32 width, i32 height);

	private:
		#ifndef WINDOWS_BUILD
		static void WebLoop();
		#endif

		Flag mFlag;

		std::vector<Window> mWindows;
	
		Window* GetWindow(GLFWwindow* windowPtr);

		static std::string smAssetsPath;

		void Release();
		void Prepare();
		void Loop();
		void Run();
	};
}

#endif
