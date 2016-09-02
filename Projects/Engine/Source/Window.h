#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "EngineUtil.h"

struct GLFWwindow;

namespace ai
{
	class ENGINE_API Window
	{
	public:
		Window();

		bool Create(const char* title, u32 width, u32 heigh, u32 samples, bool isMain);

		inline bool SetNewSize(u32 width, u32 height);

		inline u32 GetSamples() const;
		inline u32 GetWidth() const;
		inline u32 GetHeight() const;

		inline void SwapBuffers() const;

		static bool InitApi();
		static void ReleaseApi();

	private:
		GLFWwindow* mWindow;

		u32 mSamples;
		u32 mWidth;
		u32 mHeight;
	};
}

#endif
