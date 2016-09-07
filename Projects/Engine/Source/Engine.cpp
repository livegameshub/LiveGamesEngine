#include "Engine.h"
#include "Random.h"
#include "Graphics.h"

namespace ai
{
	Engine::Engine()
		: mIsStoped(false)
	{
	}

	Window* Engine::GetWindow(GLFWwindow* windowPtr)
	{
		for (u32 i = 0; i < mWindows.size(); ++i)
		{
			if (mWindows[i].GetWindowPtr() == windowPtr)
			{
				return &mWindows[i];
			}
		}

		return nullptr;
	}

	bool Engine::Setup(const char* title)
	{
		Random::Seed();

		/* init the window api */
		if (!Window::InitApi())
		{
			return false;
		}

		/* we should add at least the main window */
		Window window(Window::GetScreenSize(), 0, true);

		if (!window.Create(title))
		{
			return false;
		}

		mWindows.push_back(window);

		return true;
	}

	void Engine::Run()
	{
		const Window& window = mWindows[0];

		while (!mIsStoped && !window.IsClosing())
		{
			window.Draw();
			window.SwapBuffers();

			Window::HandleEvents();
		}

		Window::ReleaseApi();
	}

	void Engine::Stop()
	{
		mIsStoped = true;
	}

	void Engine::Prepare()
	{
	}

	void Engine::WindowResizeCallback(GLFWwindow* windowPtr, i32 width, i32 height)
	{
		Window* window = Engine::GetInstance().GetWindow(windowPtr);

		if (window && window->SetNewSize(Size<u32>(width, height)))
		{
			glViewport(0, 0, width, height);
		}
	}

	Engine& Engine::GetInstance()
	{
		static Engine instance;

		return instance;
	}
}
