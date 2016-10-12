#ifdef _DEBUG
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "EngineUtil.h"

namespace ai
{
	class ENGINE_API Console
	{
	public:
		enum ConsoleMsgType : glm::u32
		{
			IMPORTANT_MSG = 1,
			SUCCESS_MSG = 2,
			FAILED_MSG = 4,
			WARNING_MSG = 14,
			INFO_MSG = 15
		};

		static void write(const std::string& message, ConsoleMsgType msgType);

	private:
		static glm::u32 smCurrentMsgType;
	};
}

#endif // _CONSOLE_H_
#endif // _DEBUG