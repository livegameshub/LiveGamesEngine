#ifndef _RESOURCE_CONTAINER_H_
#define _RESOURCE_CONTAINER_H_

#include "Resource.h"

namespace ai
{
	struct ENGINE_API ResourceContainer
	{
		enum ResourceContainerAction : glm::u32
		{
			LOAD_ACTION = 1,
			UNLOAD_ACTION = 2
		};

		ResourceContainer(Resource* resource, const Flag& flag);

		Resource* resource;
		Flag flag;
	};
}

#endif // _RESOURCE_CONTAINER_H_
