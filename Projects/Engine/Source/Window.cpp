#include "Window.h"
#include "Graphics.h"
#include "Engine.h"

#include <glfw3.h>

namespace ai
{
	Window::Window()
		: mIsMain(false)
		, mSamples(0)
		, mWindowPtr(nullptr)
	{
	}

	Window::Window(const Size<u32>& size, u32 samples, bool isMain)
		: mIsMain(isMain)
		, mSamples(samples)
		, mSize(size)
		, mWindowPtr(nullptr)
	{
	}

	Window::~Window()
	{
	}

	bool Window::Create(const char* title)
	{
		// TODO
		// integrate maximed window option
		// glfwWindowHint(GLFW_MAXIMIZED, true);

		if (mIsMain && mSamples > 0)
		{
			glfwWindowHint(GLFW_SAMPLES, mSamples);
		}

		mWindowPtr = glfwCreateWindow(mSize.width, mSize.height, title, nullptr, nullptr);

		if (mWindowPtr == nullptr)
		{
			ReleaseApi();

			return false;
		}

		glfwMakeContextCurrent(mWindowPtr);

		if (mIsMain)
		{
			if (!Graphics::InitApi())
			{
				ReleaseApi();

				return false;
			}
			
			Graphics::CheckApiVersion();
			Graphics::CheckMaxSamples();

			InitWindowCallbacks();
		}

		return true;
	}

	bool Window::SetNewSize(const Size<u32>& size)
	{
		if (mSize != size)
		{
			mSize = size;

			return true;
		}

		return false;
	}

	u32 Window::GetSamples() const
	{
		return mSamples;
	}

	i32 Window::IsClosing() const
	{
		return glfwWindowShouldClose(mWindowPtr);
	}

	Size<u32> Window::GetScreenSize()
	{
		/* get the main monitor */
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		/* get the mode of our monitor */
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		Size<u32> size(mode->width, mode->height);

		return size;
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(mWindowPtr);
	}

	void Window::Draw() const
	{
	}

	GLFWwindow* Window::GetWindowPtr() const
	{
		return mWindowPtr;
	}

	const Size<u32>& Window::GetSize() const
	{
		return mSize;
	}

	bool Window::InitApi()
	{
		return glfwInit() ? true : false;
	}

	void Window::ReleaseApi()
	{
		glfwTerminate();
	}

	void Window::HandleEvents()
	{
		glfwPollEvents();
	}

	void Window::InitWindowCallbacks() const
	{
		glfwSetWindowSizeCallback(mWindowPtr, Engine::WindowResizeCallback);
	}
}
