#ifdef _DEBUG
#include "Console.h"

#include <windows.h>
#include <iostream>

namespace ai
{
	glm::u32 Console::smCurrentColor = WHITE;

	void* Console::smConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	void Console::SetTextColor(ConsoleColor color)
	{
		if (smCurrentColor != color)
		{
			SetConsoleTextAttribute(smConsoleHandle, color);

			smCurrentColor = color;
		}
	}

	void Console::Write(const std::string& message)
	{
		std::cout << message << std::endl;
	}

	void Console::WriteImportant(const std::string& message)
	{
		SetTextColor(BLUE);
		Write(message);
	}

	void Console::WriteWarning(const std::string& message)
	{
		SetTextColor(YELLOW);
		Write(message);
	}

	void Console::WriteSuccess(const std::string& message)
	{
		SetTextColor(GREEN);
		Write(message);
	}

	void Console::WriteFailed(const std::string& message)
	{
		SetTextColor(RED);
		Write(message);
	}

	void Console::WriteInfo(const std::string& message)
	{
		SetTextColor(WHITE);
		Write(message);
	}
}

#endif
