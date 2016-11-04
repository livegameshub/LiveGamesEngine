#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Renderer.h"

struct GLFWwindow;

namespace lg
{
	class ENGINE_API Window
	{
	public:
		Window(const ivec2& size);
		Window(const ivec2& size, u32 samples);

		~Window();

		bool create(const string& title, bool isMain);

		bool setNewSize(const ivec2& size);
		void setIsFocused(i32 isFocused);

		void swapBuffers() const;
		void draw() const;

		const ivec2& getSize() const;
		GLFWwindow* getWindowPtr() const;
		u32 getSamples() const;
		i32 isClosing() const;
		i32 isFocused() const;

		Renderer& getRenderer();
		
		// callbacks
		static void focusCallback(GLFWwindow* windowPtr, i32 isFocused);
		static void resizeCallback(GLFWwindow* windowPtr, i32 width, i32 height);

		static ivec2 getScreenSize();

		static bool initApi();
		static void releaseApi();
		static void handleEvents();

	private:
		void initCallbacks() const;

		i32 mIsFocused;
		u32 mSamples;
		ivec2 mSize;
		
		GLFWwindow* mWindowPtr;
		Renderer mRenderer;
	};
}

#endif // _WINDOW_H_
