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

		void stop();
		void pause();
		void resume();

		void addWindow(const Window& window);

		// TODO
		// setup should return an int with some specific codes
		static bool setup(const std::string& mainWindowTitle);
		static void windowResizeCallback(GLFWwindow* windowPtr, glm::i32 width, glm::i32 height);

		Window* getWindow(GLFWwindow* windowPtr);
		Window* getWindowByIndex(glm::u32 index);

		static void loadScene(glm::u32 index);
		static Engine& getInstance();

	private:
		Flag mFlag;

		std::vector<Window> mWindows;

		static void Release();

		#ifndef WINDOWS_BUILD
		static void webLoop();
		#endif // WINDOWS_BUILD

		void prepare();
		void loop();
		void run();
	};
}

#endif // _ENGINE_H_
