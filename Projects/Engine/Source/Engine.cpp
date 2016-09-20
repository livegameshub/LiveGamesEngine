#include "Engine.h"
#include "Random.h"
#include "Graphics.h"
#include "Time.h"
#include <iostream>

#ifdef _DEBUG
#include "FpsCounter.h"
#endif

#ifndef WINDOWS_BUILD
#include <emscripten/emscripten.h>
#endif

namespace ai
{
	std::string Engine::smAssetsPath;

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

	#ifndef WINDOWS_BUILD

	void Engine::WebLoop()
	{
		GetInstance().Loop();
	}

	#endif

	bool Engine::Setup(const std::string& title, const std::string& assetsPath)
	{
		smAssetsPath = assetsPath;

		/* init the window api */
		if (!Window::InitApi())
		{
			return false;
		}

		Size<u32> size = Window::GetScreenSize();

		#if defined _DEBUG or !defined WINDOWS_BUILD

		size = Size<u32>(1024, 600);

		#endif

		/* we should add at least the main window */
		Window window(size, 0, true);

		if (!window.Create(title))
		{
			return false;
		}

		mWindows.push_back(window);

		/* prepare the engine */
		Prepare();

		#ifdef WINDOWS_BUILD
		/* run the engine */
		Run();

		#else
		/* run the main loop */
		emscripten_set_main_loop(WebLoop, 0, true);
		#endif

		/* release all the resources after we finish */
		Release();

		return true;
	}

	void Engine::Prepare()
	{
		/* seed the random value */
		Random::Seed();

		Time::Start();
	}

	void Engine::Loop()
	{
		Window& main_window = mWindows[0];

		/* check if we are not on break with this loop */
		if (!mFlag.IsSet(PAUSE_FLAG))
		{
			Time::Update();

			#ifdef _DEBUG

			FpsCounter::Update();

			#endif

			main_window.Draw();
			main_window.SwapBuffers();
		}
	}

	void Engine::Run()
	{
		/* on the first position should be the main window */

		while (!mFlag.IsSet(STOP_FLAG) && !mWindows[0].IsClosing())
		{
			Loop();

			/* handle the events everytime */
			Window::HandleEvents();
		}
	}

	void Engine::Release()
	{
		Window::ReleaseApi();
	}

	void Engine::Stop()
	{
		mFlag += STOP_FLAG;
	}

	void Engine::Pause()
	{
		mFlag += PAUSE_FLAG;
	}

	void Engine::Resume()
	{
		mFlag -= PAUSE_FLAG;
	}

	void Engine::WindowResizeCallback(GLFWwindow* windowPtr, i32 width, i32 height)
	{
		Window* window = GetInstance().GetWindow(windowPtr);

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

	const std::string& Engine::GetAssetsPath()
	{
		return smAssetsPath;
	}
}
