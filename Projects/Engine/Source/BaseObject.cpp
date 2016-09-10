#include "BaseObject.h"

namespace ai
{
	BaseObject::BaseObject(u32 id)
		: mId(id)
	{
	}

	BaseObject::BaseObject(u32 id, const Flag& flag)
		: mFlag(flag)
		, mId(id)
	{
	}

	BaseObject::~BaseObject()
	{
	}

	void BaseObject::SetId(u32 id)
	{
		mId = id;
	}

	void BaseObject::SetFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	u32 BaseObject::GetId() const
	{
		return mId;
	}

	const Flag& BaseObject::GetFlag() const
	{
		return mFlag;
	}
}
