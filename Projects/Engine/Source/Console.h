#ifdef _DEBUG
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "EngineUtil.h"

namespace lg
{
	class ENGINE_API Console
	{
	public:
		enum MsgType : u32
		{
			IMPORTANT_MSG = 1,
			SUCCESS_MSG = 2,
			FAILED_MSG = 4,
			WARNING_MSG = 14,
			INFO_MSG = 15
		};

		static void write(const string& message, MsgType msgType);

	private:
		static u32 smCurrentMsgType;
	};
}

#endif // _CONSOLE_H_
#endif // _DEBUG