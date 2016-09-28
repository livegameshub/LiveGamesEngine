#include "Engine.h"
#include "Random.h"
#include "Graphics.h"
#include "Time.h"
#include "SceneManager.h"

#ifdef _DEBUG
	#include "FpsCounter.h"
#endif

#ifndef WINDOWS_BUILD
	#include <emscripten/emscripten.h>
#endif

namespace ai
{
	Window* Engine::GetWindow(GLFWwindow* windowPtr)
	{
		for (glm::u32 i = 0; i < mWindows.size(); ++i)
		{
			if (mWindows[i].GetWindowPtr() == windowPtr)
			{
				return &mWindows[i];
			}
		}

		return nullptr;
	}

	Window* Engine::GetWindowByIndex(glm::u32 index)
	{
		if (index < mWindows.size())
		{
			return &mWindows[index];
		}

		return nullptr;
	}

	#ifndef WINDOWS_BUILD

	void Engine::WebLoop()
	{
		GetInstance().Loop();
	}

	#endif

	bool Engine::Setup(const std::string& mainWindowTitle)
	{
		/* init the window api */
		if (!Window::InitApi())
		{
			return false;
		}

		#if (defined _DEBUG || !defined WINDOWS_BUILD)
			glm::ivec2 size = glm::ivec2(1024, 600);
		#else 
			glm::ivec2 size = Window::GetScreenSize();
		#endif

		/* we should add at least the main window */
		Window window(size, 0);

		if (!window.Create(mainWindowTitle, true))
		{
			return false;
		}

		Engine& engine = Engine::GetInstance();

		/* the first element is the main window */
		engine.AddWindow(window);

		/* prepare the engine */
		engine.Prepare();

		#ifdef WINDOWS_BUILD
			/* run the engine */
			engine.Run();
		#else
			/* run the main loop */
			emscripten_set_main_loop(WebLoop, 0, true);
		#endif

		/* release all the resources after we finish */
		engine.Release();

		return true;
	}

	void Engine::Prepare()
	{
		/* seed the random value */
		Random::Seed();

		Time::Start();

		/* the first scene is the main one */
		SceneManager::GetInstance().SetMainScene(0);
	}

	void Engine::Loop()
	{
		Window& main_window = mWindows[0];

		/* check if we are not on break with this loop */
		if (!mFlag.IsSet(ENGINE_PAUSE_FLAG))
		{
			Time::Update();

			#ifdef _DEBUG

			FpsCounter::Update();

			#endif

			SceneManager::GetInstance().Update();

			main_window.Draw();
			main_window.SwapBuffers();
		}
	}

	void Engine::Run()
	{
		/* on the first position should be the main window */

		while (!mFlag.IsSet(ENGINE_STOP_FLAG) && !mWindows[0].IsClosing())
		{
			Loop();

			/* handle the events everytime */
			Window::HandleEvents();
		}
	}

	void Engine::Release()
	{
		SceneManager::GetInstance().Release();

		Window::ReleaseApi();
	}

	void Engine::Stop()
	{
		mFlag += ENGINE_STOP_FLAG;
	}

	void Engine::Pause()
	{
		mFlag += ENGINE_PAUSE_FLAG;
	}

	void Engine::Resume()
	{
		mFlag -= ENGINE_PAUSE_FLAG;
	}

	void Engine::AddWindow(const Window& window)
	{
		mWindows.push_back(window);
	}

	void Engine::WindowResizeCallback(GLFWwindow* windowPtr, glm::i32 width, glm::i32 height)
	{
		Window* window = GetInstance().GetWindow(windowPtr);

		if (window && window->SetNewSize(glm::ivec2(width, height)))
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
