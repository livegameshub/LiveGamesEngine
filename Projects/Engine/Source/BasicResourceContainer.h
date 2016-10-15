#ifndef _BASIC_RESOURCE_CONTAINER_H_
#define _BASIC_RESOURCE_CONTAINER_H_

#include "BasicResource.h"

namespace ai
{
	struct ENGINE_API BasicResourceContainer
	{
		enum BasicResourceContainerAction : glm::u32
		{
			LOAD_ACTION = 1,
			UNLOAD_ACTION = 2
		};

		BasicResourceContainer(BasicResource* resource, const Flag& flag);

		BasicResource* resource;
		Flag flag;
	};
}

#endif // _BASIC_RESOURCE_CONTAINER_H_
