#ifdef _DEBUG
#include "Console.h"

#include <windows.h>
#include <iostream>

namespace lg
{
	glm::u32 Console::smCurrentMsgType = INFO_MSG;

	void Console::write(const std::string& message, MsgType msgType)
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

#endif // _DEBUG
