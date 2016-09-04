#include "Application.h"
#include "Engine.h"

namespace ai
{
	void Application::Start()
	{
		Engine& engine = Engine::GetInstance();

		/* try to setup the engine */

		if (engine.Setup("Live Games Engine"))
		{
			/* add some scenes */

			engine.Run();
		}
	}
}
