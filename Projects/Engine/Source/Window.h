#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "EngineUtil.h"
#include "Renderer.h"

struct GLFWwindow;

namespace ai
{
	class ENGINE_API Window
	{
	public:
		Window();
		Window(const glm::ivec2& size, glm::u32 samples, bool isMain = false);

		~Window();

		bool Create(const std::string& title = "");

		bool SetNewSize(const glm::ivec2& size);
		void SwapBuffers() const;
		void Draw();

		inline Renderer& GetRenderer();

		inline const glm::ivec2& GetSize() const;
		inline glm::u32 GetSamples() const;

		GLFWwindow* GetWindowPtr() const;
		glm::i32 IsClosing() const;
		
		static glm::ivec2 GetScreenSize();

		static bool InitApi();
		static void ReleaseApi();
		static void HandleEvents();

	private:
		bool mIsMain;

		glm::u32 mSamples;
		glm::ivec2 mSize;
		
		GLFWwindow* mWindowPtr;
		Renderer mRenderer;

		void InitWindowCallbacks() const;
	};
}

#endif
