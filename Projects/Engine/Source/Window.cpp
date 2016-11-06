#include "Window.h"
#include "Graphics.h"
#include "Engine.h"
#include "Input.h"
#include "Camera.h"
#include "Scenes.h"
#include "Scene.h"

#include <glfw/glfw3.h>

namespace lg
{
	Window::Window(const ivec2& size)
		: mIsFocused(1)
		, mSamples(0)
		, mSize(size)
		, mWindowPtr(nullptr)
	{
	}

	Window::Window(const ivec2& size, u32 samples)
		: mIsFocused(1)
		, mSamples(samples)
		, mSize(size)
		, mWindowPtr(nullptr)
	{
	}

	Window::~Window()
	{
	}

	bool Window::create(const string& title, bool isMain)
	{
		if (isMain)
		{
			#if (defined NDEBUG && defined WINDOWS_BUILD)

			// in the release we should be maximmized
			glfwWindowHint(GLFW_MAXIMIZED, true);

			#endif // (!defined _DEBUG && defined WINDOWS_BUILD)

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
			initCallbacks();
		}

		return true;
	}

	bool Window::setNewSize(const ivec2& size)
	{
		if (mSize != size)
		{
			mSize = size;

			return true;
		}

		return false;
	}

	void Window::setIsFocused(i32 isFocused)
	{
		mIsFocused = isFocused;
	}

	u32 Window::getSamples() const
	{
		return mSamples;
	}

	i32 Window::isClosing() const
	{
		return glfwWindowShouldClose(mWindowPtr);
	}

	i32 Window::isFocused() const
	{
		return mIsFocused;
	}

	ivec2 Window::getScreenSize()
	{
		/* get the main monitor */
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		/* get the mode of our monitor */
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		return ivec2(mode->width, mode->height);
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(mWindowPtr);
	}

	void Window::draw() const
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

	const ivec2& Window::getSize() const
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

	void Window::initCallbacks() const
	{
		glfwSetKeyCallback(mWindowPtr, Input::keyboardKeysCallback);
		glfwSetCursorPosCallback(mWindowPtr, Input::mousePositionCallback);
		glfwSetMouseButtonCallback(mWindowPtr, Input::mouseClicksCallback);

		glfwSetWindowFocusCallback(mWindowPtr, focusCallback);
		glfwSetWindowSizeCallback(mWindowPtr, resizeCallback);
	}

	void Window::focusCallback(GLFWwindow* windowPtr, i32 isFocused)
	{
		Window* window = Engine::instance().getWindow(windowPtr);
		assert(window != nullptr);

		window->setIsFocused(isFocused);
	}

	void Window::resizeCallback(GLFWwindow* windowPtr, i32 width, i32 height)
	{
		if (width == 0 || height == 0)
		{
			// no resize if we have 0 values
			// it will cause an error
			return;
		}

		Window* window = Engine::instance().getWindow(windowPtr);
		assert(window != nullptr);

		ivec2 size(width, height);

		if (window->setNewSize(size))
		{
			/* update the cameras from the main scene with the new size */

			const Scene* scene = Scenes::instance().getMainScene();
			assert(scene != nullptr);

			for (Camera* camera : scene->getCameras())
			{
				assert(camera != nullptr);

				if (!camera->hasCustomSize())
				{
					camera->setSize(size);
				}
			}

			glViewport(0, 0, width, height);
		}
	}
}
