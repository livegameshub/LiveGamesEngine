#include "Window.h"
#include "Graphics.h"

#include <glfw3.h>

namespace ai
{
	Window::Window()
		: mWindow(nullptr)
		, mSamples(0)
		, mWidth(0)
		, mHeight(0)
	{
	}

	bool Window::Create(const char* title, u32 width, u32 height, u32 samples, bool isMain)
	{
		if (isMain)
		{
			if (!InitApi())
			{
				return false;
			}

			if (samples > 0)
			{
				glfwWindowHint(GLFW_SAMPLES, samples);
			}
		}

		mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (mWindow == nullptr)
		{
			ReleaseApi();

			return false;
		}

		glfwMakeContextCurrent(mWindow);

		if (isMain)
		{
			if (!Graphics::InitApi())
			{
				ReleaseApi();

				return false;
			}
			
			Graphics::CheckApiVersion();
			Graphics::CheckMaxSamples();
		}

		SetNewSize(width, height);
		mSamples = samples;

		return true;
	}

	bool Window::SetNewSize(u32 width, u32 height)
	{
		if (width && height && 
			mWidth != width && mHeight != height)
		{
			mWidth = width;
			mHeight = height;

			return true;
		}

		return false;
	}

	u32 Window::GetSamples() const
	{
		return mSamples;
	}

	u32 Window::GetWidth() const
	{
		return mWidth;
	}

	u32 Window::GetHeight() const
	{
		return mHeight;
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(mWindow);
	}

	bool Window::InitApi()
	{
		return glfwInit() ? true : false;
	}

	void Window::ReleaseApi()
	{
		glfwTerminate();
	}
}
