#include "Window.h"
#include "Graphics.h"
#include "Engine.h"
#include "Input.h"

#include <glfw/glfw3.h>

namespace ai
{
	Window::Window(const glm::ivec2& size)
		: mSamples(0)
		, mSize(size)
		, mWindowPtr(nullptr)
	{
	}

	Window::Window(const glm::ivec2& size, glm::u32 samples)
		: mSamples(samples)
		, mSize(size)
		, mWindowPtr(nullptr)
	{
	}

	Window::~Window()
	{
	}

	bool Window::create(const std::string& title, bool isMain)
	{
		if (isMain)
		{
			#ifndef _DEBUG

			// in the release we should be maximmized
			glfwWindowHint(GLFW_MAXIMIZED, true);

			#endif // _DEBUG

			if (mSamples > 0)
			{
				glfwWindowHint(GLFW_SAMPLES, mSamples);
			}
		}

		mWindowPtr = glfwCreateWindow(mSize.x, mSize.y, title.c_str() , nullptr, nullptr);

		if (mWindowPtr == nullptr)
		{
			releaseApi();

			return false;
		}

		glfwMakeContextCurrent(mWindowPtr);

		if (isMain)
		{
			if (!Graphics::initApi())
			{
				releaseApi();

				return false;
			}
			
			#ifdef WINDOWS_BUILD

			Graphics::checkApiVersion();
			Graphics::checkMaxSamples();

			#endif // WINDOWS_BUILD

			/* init the callbacks for the main window */
			initWindowCallbacks();
		}

		return true;
	}

	bool Window::setNewSize(const glm::ivec2& size)
	{
		if (mSize != size)
		{
			mSize = size;

			return true;
		}

		return false;
	}

	glm::u32 Window::getSamples() const
	{
		return mSamples;
	}

	glm::i32 Window::isClosing() const
	{
		return glfwWindowShouldClose(mWindowPtr);
	}

	glm::ivec2 Window::getScreenSize()
	{
		/* get the main monitor */
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		/* get the mode of our monitor */
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		return glm::ivec2(mode->width, mode->height);
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(mWindowPtr);
	}

	void Window::draw()
	{
		mRenderer.draw();
	}

	GLFWwindow* Window::getWindowPtr() const
	{
		return mWindowPtr;
	}

	Renderer& Window::getRenderer()
	{
		return mRenderer;
	}

	const glm::ivec2& Window::getSize() const
	{
		return mSize;
	}

	bool Window::initApi()
	{
		return glfwInit() ? true : false;
	}

	void Window::releaseApi()
	{
		glfwTerminate();
	}

	void Window::handleEvents()
	{
		glfwPollEvents();
	}

	void Window::initWindowCallbacks() const
	{
		glfwSetKeyCallback(mWindowPtr, Input::keyboardKeysCallback);
		glfwSetCursorPosCallback(mWindowPtr, Input::mousePositionCallback);
		glfwSetMouseButtonCallback(mWindowPtr, Input::mouseClicksCallback);

		glfwSetWindowSizeCallback(mWindowPtr, Engine::windowResizeCallback);
	}
}
