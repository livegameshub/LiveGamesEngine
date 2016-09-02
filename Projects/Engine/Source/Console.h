#ifdef _DEBUG
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "EngineUtil.h"

namespace ai
{
	class ENGINE_API Console
	{
	public:
		enum ConsoleColor : u32
		{
			BLUE = 1,
			GREEN = 2,
			RED = 4,
			YELLOW = 14,
			WHITE = 15
		};

		static void WriteImportant(const std::string& message);
		static void WriteWarning(const std::string& message);
		static void WriteSuccess(const std::string& message);
		static void WriteFailed(const std::string& message);
		static void WriteInfo(const std::string& message);

	private:
		static u32 smCurrentColor;
		static void* smConsoleHandle;

		static void SetTextColor(ConsoleColor color);
		static void Write(const std::string& message);
	};
}

#endif
#endif