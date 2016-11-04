#ifdef _DEBUG
#include "Console.h"

#include <windows.h>
#include <iostream>

namespace lg
{
	u32 Console::smCurrentMsgType = INFO_MSG;

	void Console::write(const string& message, MsgType msgType)
	{
		if (smCurrentMsgType != msgType)
		{
			static auto consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(consoleHandle, msgType);

			smCurrentMsgType = msgType;
		}

		cout << message << endl;
	}
}

#endif // _DEBUG
