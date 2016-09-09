#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "EngineUtil.h"
#include "Renderer.h"
#include "Size.h"

struct GLFWwindow;

namespace ai
{
	class ENGINE_API Window
	{
	public:
		Window();
		Window(const Size<u32>& size, u32 samples, bool isMain = false);
		~Window();

		bool Create(const char* title = "");

		inline bool SetNewSize(const Size<u32>& size);
		inline void SwapBuffers() const;
		inline void Draw();

		inline GLFWwindow* GetWindowPtr() const;
		inline Renderer& GetRenderer();

		inline const Size<u32>& GetSize() const;
		inline u32 GetSamples() const;
		inline i32 IsClosing() const;
		
		static Size<u32> GetScreenSize();

		static bool InitApi();
		static void ReleaseApi();
		static void HandleEvents();

	private:
		bool mIsMain;

		u32 mSamples;
		Size<u32> mSize;
		
		GLFWwindow* mWindowPtr;
		Renderer mRenderer;

		void InitWindowCallbacks() const;
	};
}

#endif
