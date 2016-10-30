#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Flag.h"
#include "Window.h"

struct GLFWwindow;

namespace lg
{
	class ENGINE_API Engine
	{
	public:
		enum EngineFlag : glm::u32
		{
			ENGINE_STOP_FLAG = 1,
			ENGINE_PAUSE_FLAG = 2
		};

		void addWindow(const Window& window);

		// TODO
		// setup should return an int with some specific codes
		static bool setup(const std::string& mainWindowTitle);
		static void Release();

		Window* getWindow(GLFWwindow* windowPtr);
		Window* getWindowByIndex(glm::u32 index);

		static void loadScene(glm::u32 index);
		static Engine& getInstance();

		void resume();
		void pause();
		void stop();
		
	private:
		#ifndef WINDOWS_BUILD
		static void webLoop();
		#endif // WINDOWS_BUILD

		void prepare();
		void loop();
		void run();

		std::vector<Window> mWindows;
		Flag mFlag;
	};
}

#endif // _ENGINE_H_
