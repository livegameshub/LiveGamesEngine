#include "Window.h"
#include "Graphics.h"
#include "Engine.h"
#include "Input.h"

#ifdef WINDOWS_BUILD
#include <glfw3.h>
#else
// we have this choice for emscripten
#include <glfw/glfw3.h>
#endif

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

	bool Window::Create(const std::string& title)
	{
		// TODO
		// integrate maximed window option
		// glfwWindowHint(GLFW_MAXIMIZED, true);

		if (mIsMain && mSamples > 0)
		{
			glfwWindowHint(GLFW_SAMPLES, mSamples);
		}

		mWindowPtr = glfwCreateWindow(mSize.width, mSize.height, title.c_str() , nullptr, nullptr);

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
			
			#ifdef WINDOWS_BUILD

			Graphics::CheckApiVersion();
			Graphics::CheckMaxSamples();

			#endif

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

	void Window::Draw()
	{
		mRenderer.Draw();
	}

	GLFWwindow* Window::GetWindowPtr() const
	{
		return mWindowPtr;
	}

	Renderer& Window::GetRenderer()
	{
		return mRenderer;
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
		glfwSetKeyCallback(mWindowPtr, Input::KeyboardKeysCallback);
		glfwSetCursorPosCallback(mWindowPtr, Input::MousePositionCallback);
		glfwSetMouseButtonCallback(mWindowPtr, Input::MouseClicksCallback);

		glfwSetWindowSizeCallback(mWindowPtr, Engine::WindowResizeCallback);
	}
}
