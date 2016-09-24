#include "BasicNode.h"

namespace ai
{
	BasicNode::BasicNode(u32 id)
		: BasicElement(id)
		, mIsEnabled(true)
		, mNodeType(BASIC_NODE)
	{
	}

	BasicNode::BasicNode(u32 id, i32 type)
		: BasicElement(id)
		, mIsEnabled(true)
		, mNodeType(type)
	{
	}

	BasicNode::BasicNode(u32 id, i32 type, const Flag& flag)
		: BasicElement(id, flag)
		, mIsEnabled(true)
		, mNodeType(type)
	{
	}

	BasicNode::BasicNode(u32 id, const Flag& flag)
		: BasicElement(id, flag)
		, mIsEnabled(true)
		, mNodeType(BASIC_NODE)
	{
	}

	BasicNode::~BasicNode()
	{
	}

	void BasicNode::SetEnabled(bool value)
	{
		mIsEnabled = value;
	}

	bool BasicNode::IsEnabled() const
	{
		return mIsEnabled;
	}
}
