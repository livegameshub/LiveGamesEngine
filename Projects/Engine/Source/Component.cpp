#include "Component.h"

namespace lg
{
	Component::Component()
		: mIsEnabled(true)
		, mType(-1)
	{
	}

	Component::Component(glm::i32 type)
		: mIsEnabled(true)
		, mType(type)
	{
	}

	Component::Component(glm::i32 type, const Flag& flag)
		: mIsEnabled(true)
		, mFlag(flag)
		, mType(type)
	{
	}

	Component::Component(const Flag& flag)
		: mIsEnabled(true)
		, mFlag(flag)
		, mType(-1)
	{
	}

	Component::~Component()
	{
	}

	const Flag& Component::getFlag() const
	{
		return mFlag;
	}

	glm::i32 Component::getType() const
	{
		return mType;
	}

	void Component::setEnabled(bool value)
	{
		mIsEnabled = value;
	}

	bool Component::isEnabled() const
	{
		return mIsEnabled;
	}

	void Component::setFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	void Component::setType(glm::i32 type)
	{
		mType = type;
	}
}
