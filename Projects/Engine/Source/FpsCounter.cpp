#ifdef _DEBUG
#include "FpsCounter.h"
#include "Time.h"
#include "Console.h"

namespace lg
{
	u32 FpsCounter::smFrames = 0;
	f32 FpsCounter::smFramesTime = 0.0f;

	void FpsCounter::update()
	{
		++smFrames;

		smFramesTime += Time::getDeltaTime();

		if (smFramesTime >= 1.0f)
		{
			string message = "Fps: " + to_string(smFrames);

			if (smFrames < 30)
			{
				Console::write(message, Console::MsgType::FAILED_MSG);
			}
			else if (smFrames < 60)
			{
				Console::write(message, Console::MsgType::WARNING_MSG);
			}
			else
			{
				Console::write(message, Console::MsgType::INFO_MSG);
			}

			smFramesTime = 0.0f;
			smFrames = 0;
		}
	}
}

#endif // _DEBUG
