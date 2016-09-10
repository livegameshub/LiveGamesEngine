#include "Application.h"
#include "Engine.h"

namespace ai
{
	void Application::Start(const char* appName)
	{
		Engine& engine = Engine::GetInstance();

		/* try to setup the engine */

		if (engine.Setup(appName))
		{
			/* prepare the engine */
			engine.Prepare();
			engine.Run();

			/* release all the resources */
			engine.Release();
		}
	}
}
