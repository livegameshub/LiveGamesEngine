#include "BasicNode.h"

namespace ai
{
	BasicNode::BasicNode(u32 id)
		: BasicElement(id)
	{
	}

	BasicNode::BasicNode(u32 id, const Flag& flag)
		: BasicElement(id, flag)
	{
	}

	BasicNode::~BasicNode()
	{
	}
}
