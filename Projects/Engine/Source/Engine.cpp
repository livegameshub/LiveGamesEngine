#include "Engine.h"
#include "Random.h"

namespace ai
{
	bool Engine::Setup(const char* title)
	{
		Random::Seed();

		Window window(Size<u32>(800, 600), 0, true);

		if (!window.Create(title))
		{
			return false;
		}

		mWindows.push_back(window);

		return true;
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
