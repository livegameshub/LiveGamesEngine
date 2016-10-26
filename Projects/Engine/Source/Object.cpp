#include "Object.h"

namespace lg
{
	Object::Object(glm::u32 id)
		: mId(id)
	{
	}

	Object::Object(glm::u32 id, const Flag& flag)
		: mId(id)
		, mFlag(flag)
	{
	}

	Object::~Object()
	{
	}

	void Object::setId(glm::u32 id)
	{
		mId = id;
	}

	void Object::setFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	glm::u32 Object::getId() const
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
