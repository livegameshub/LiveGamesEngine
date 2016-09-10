#include "Application.h"
#include "Engine.h"

namespace ai
{
	Application::Application(const std::string& appName)
		: mAppName(appName)
	{
	}

	void Application::Start() const
	{
		Engine& engine = Engine::GetInstance();

		/* try to setup the engine */

		if (engine.Setup(mAppName.c_str()))
		{
			/* prepare the engine */
			engine.Prepare();
			engine.Run();

			/* release all the resources */
			engine.Release();
		}
	}
}
