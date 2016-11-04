#include "Object.h"

namespace lg
{
	Object::Object(u32 id)
		: mId(id)
	{
	}

	Object::Object(u32 id, const Flag& flag)
		: mId(id)
		, mFlag(flag)
	{
	}

	Object::~Object()
	{
	}

	void Object::setId(u32 id)
	{
		mId = id;
	}

	void Object::setFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	u32 Object::getId() const
	{
		return mId;
	}

	const Flag& Object::getFlag() const
	{
		return mFlag;
	}

	Flag& Object::getFlag()
	{
		return mFlag;
	}
}
