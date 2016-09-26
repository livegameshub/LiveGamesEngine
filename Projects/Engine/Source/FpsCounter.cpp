#ifdef _DEBUG
#include "FpsCounter.h"
#include "Time.h"
#include "Console.h"

namespace ai
{
	glm::f32 FpsCounter::smFramesTime = 0.0f;
	glm::u32 FpsCounter::smFrames = 0;

	void FpsCounter::Update()
	{
		++smFrames;

		smFramesTime += Time::GetDeltaTime();

		if (smFramesTime >= 1.0f)
		{
			std::string message = "Fps: " + std::to_string(smFrames) + 
								  " dt: " + std::to_string(Time::GetDeltaTime() * 1000.0f) + " ms";

			if (smFrames < 30)
			{
				Console::WriteFailed(message);
			}
			else if (smFrames < 60)
			{
				Console::WriteWarning(message);
			}
			else
			{
				Console::WriteInfo(message);
			}

			smFramesTime = 0.0f;
			smFrames = 0;
		}
	}
}

#endif
