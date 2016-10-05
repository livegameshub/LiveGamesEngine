#ifdef _DEBUG
#include "Console.h"

#include <windows.h>
#include <iostream>

namespace ai
{
	glm::u32 Console::smCurrentMsgType = INFO_MSG;

	void Console::Write(const std::string& message, ConsoleMsgType msgType)
	{
		if (smCurrentMsgType != msgType)
		{
			static auto consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(consoleHandle, msgType);

			smCurrentMsgType = msgType;
		}

		std::cout << message << std::endl;
	}
}

#endif
