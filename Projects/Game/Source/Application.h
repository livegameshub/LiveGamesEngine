#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Platform.h"

namespace ai
{
	class Application
	{
	public:
		Application(const std::string& appName);

		void Start() const;

	private:
		std::string mAppName;
	};
}

#endif
