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
		void swapBuffers() const;
		void draw() const;

		Renderer& getRenderer();

		const glm::ivec2& getSize() const;
		glm::u32 getSamples() const;

		GLFWwindow* getWindowPtr() const;
		glm::i32 isClosing() const;
		
		static glm::ivec2 getScreenSize();

		static bool initApi();
		static void releaseApi();
		static void handleEvents();

	private:
		glm::u32 mSamples;
		glm::ivec2 mSize;
		
		GLFWwindow* mWindowPtr;
		Renderer mRenderer;

		void initWindowCallbacks() const;
	};
}

#endif // _WINDOW_H_
