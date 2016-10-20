#include "Engine.h"
#include "Random.h"
#include "Graphics.h"
#include "Time.h"
#include "Scenes.h"
#include "Resources.h"
#include "Camera.h"
#include "Scene.h"

#ifdef _DEBUG
	#include "FpsCounter.h"
#endif // _DEBUG

#ifndef WINDOWS_BUILD
	#include <emscripten/emscripten.h>
#endif // WINDOWS_BUILD

namespace ai
{
	Window* Engine::getWindow(GLFWwindow* windowPtr)
	{
		for (glm::u32 i = 0; i < mWindows.size(); ++i)
		{
			if (mWindows[i].getWindowPtr() == windowPtr)
			{
				return &mWindows[i];
			}
		}

		return nullptr;
	}

	Window* Engine::getWindowByIndex(glm::u32 index)
	{
		assert(index < mWindows.size());

		return &mWindows[index];
	}

	#ifndef WINDOWS_BUILD

	void Engine::webLoop()
	{
		getInstance().loop();
	}

	#endif // WINDOWS_BUILD

	bool Engine::setup(const std::string& mainWindowTitle)
	{
		/* init the window api */
		if (!Window::initApi())
		{
			return false;
		}

		#if (defined _DEBUG || !defined WINDOWS_BUILD)
			glm::ivec2 size = glm::ivec2(1024, 600);
		#else 
			glm::ivec2 size = Window::getScreenSize();
		#endif // (defined _DEBUG || !defined WINDOWS_BUILD)

		/* we should add at least the main window */
		Window window(size, 0);

		if (!window.create(mainWindowTitle, true))
		{
			return false;
		}

		/* the first element is the main window */
		getInstance().addWindow(window);

		/* prepare the engine */
		getInstance().prepare();

		#ifdef WINDOWS_BUILD
			/* run the engine */
			getInstance().run();
		#else
			/* run the main loop */
			emscripten_set_main_loop(webLoop, 0, true);
		#endif // WINDOWS_BUILD

		/* release all the resources after we finish */
		Release();

		return true;
	}

	void Engine::prepare()
	{
		/* seed the random value */
		Random::seed();

		/* start to count the time */
		Time::start();

		/* init the renderer */
		Renderer::init();

		/* the first scene is the main one */
		Scenes::getInstance().setMainScene(0);
	}

	void Engine::loop()
	{
		const Window& main_window = mWindows[0];

		/* check if we are not on break with this loop */
		if (!mFlag.isSet(ENGINE_PAUSE_FLAG))
		{
			Time::update();

			#ifdef _DEBUG

			FpsCounter::update();

			#endif // _DEBUG

			Scenes::getInstance().update();

			main_window.draw();
			main_window.swapBuffers();
		}
	}

	void Engine::run()
	{
		/* on the first position should be the main window */

		while (!mFlag.isSet(ENGINE_STOP_FLAG) && !mWindows[0].isClosing())
		{
			loop();

			/* handle the events everytime */
			Window::handleEvents();
		}
	}

	void Engine::Release()
	{
		Scenes::getInstance().release();
		Resources::getInstance().release();

		Window::releaseApi();
	}

	void Engine::stop()
	{
		mFlag += ENGINE_STOP_FLAG;
	}

	void Engine::pause()
	{
		mFlag += ENGINE_PAUSE_FLAG;
	}

	void Engine::resume()
	{
		mFlag -= ENGINE_PAUSE_FLAG;
	}

	void Engine::addWindow(const Window& window)
	{
		mWindows.push_back(window);
	}

	void Engine::windowResizeCallback(GLFWwindow* windowPtr, glm::i32 width, glm::i32 height)
	{
		glm::ivec2 size(width, height);

		Window* window = getInstance().getWindow(windowPtr);

		assert(window != nullptr);

		if (window->setNewSize(size))
		{
			/* update the cameras from the main scene with the new size */

			for (Camera* camera : Scenes::getInstance().getMainScene()->getCameras())
			{
				assert(camera != nullptr);

				if (camera->hasCustomViewSize() == false)
				{
					camera->setViewSize(size);
				}
			}

			glViewport(0, 0, width, height);
		}
	}

	Engine& Engine::getInstance()
	{
		static Engine instance;

		return instance;
	}
}
