#ifndef _BASIC_NODE_H_
#define _BASIC_NODE_H_

#include "BasicElement.h"

namespace ai
{
	class ENGINE_API BasicNode : public BasicElement
	{
	public:
		BasicNode(u32 id);
		BasicNode(u32 id, const Flag& flag);

		virtual ~BasicNode();
	};
}

#endif
