#include "Engine.h"
#include "Random.h"

namespace ai
{
	void Engine::Setup(const char* title)
	{
		Random::Seed();

		/* we should add at least the main window */
		Window window(Size<u32>(800, 600), 0, true);

		if (window.Create(title))
		{
			mWindows.push_back(window);

			Run();
		}
	}

	void Engine::Run()
	{
		Window& window = mWindows[0];

		while (!window.IsClosing())
		{
			window.SwapBuffers();

			Window::HandleEvents();
		}

		Window::ReleaseApi();
	}

	void Engine::WindowResizeCallback(GLFWwindow* window, i32 width, i32 height)
	{
	}

	Engine& Engine::GetInstance()
	{
		static Engine instance;

		return instance;
	}
}
