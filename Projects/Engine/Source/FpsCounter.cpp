#ifdef _DEBUG
#include "FpsCounter.h"
#include "Time.h"
#include "Console.h"

namespace ai
{
	glm::u32 FpsCounter::smFrames = 0;
	glm::f32 FpsCounter::smFramesTime = 0.0f;

	void FpsCounter::update()
	{
		++smFrames;

		smFramesTime += Time::GetDeltaTime();

		if (smFramesTime >= 1.0f)
		{
			std::string message = "Fps: " + std::to_string(smFrames);

			if (smFrames < 30)
			{
				Console::write(message, Console::ConsoleMsgType::FAILED_MSG);
			}
			else if (smFrames < 60)
			{
				Console::write(message, Console::ConsoleMsgType::WARNING_MSG);
			}
			else
			{
				Console::write(message, Console::ConsoleMsgType::INFO_MSG);
			}

			smFramesTime = 0.0f;
			smFrames = 0;
		}
	}
}

#endif
