#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Renderer.h"

struct GLFWwindow;

namespace lg
{
	class ENGINE_API Window
	{
	public:
		Window(const glm::ivec2& size);
		Window(const glm::ivec2& size, glm::u32 samples);

		~Window();

		bool create(const std::string& title, bool isMain);

		bool setNewSize(const glm::ivec2& size);
		void setIsFocused(glm::i32 isFocused);

		void swapBuffers() const;
		void draw() const;

		const glm::ivec2& getSize() const;
		GLFWwindow* getWindowPtr() const;
		glm::u32 getSamples() const;
		glm::i32 isClosing() const;
		glm::i32 isFocused() const;

		Renderer& getRenderer();
		
		// callbacks
		static void focusCallback(GLFWwindow* windowPtr, glm::i32 isFocused);
		static void resizeCallback(GLFWwindow* windowPtr, glm::i32 width, glm::i32 height);

		static glm::ivec2 getScreenSize();

		static bool initApi();
		static void releaseApi();
		static void handleEvents();

	private:
		void initCallbacks() const;

		glm::i32 mIsFocused;
		glm::u32 mSamples;
		glm::ivec2 mSize;
		
		GLFWwindow* mWindowPtr;
		Renderer mRenderer;
	};
}

#endif // _WINDOW_H_
