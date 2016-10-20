#include "Component.h"

namespace ai
{
	Component::Component()
		: mIsEnabled(true)
		, mComponentType(-1)
	{
	}

	Component::Component(glm::i32 type)
		: mIsEnabled(true)
		, mComponentType(type)
	{
	}

	Component::Component(glm::i32 type, const Flag& flag)
		: mIsEnabled(true)
		, mFlag(flag)
		, mComponentType(type)
	{
	}

	Component::Component(const Flag& flag)
		: mIsEnabled(true)
		, mFlag(flag)
		, mComponentType(-1)
	{
	}

	Component::~Component()
	{
	}

	const Flag& Component::getFlag() const
	{
		return mFlag;
	}

	glm::i32 Component::getComponentType() const
	{
		return mComponentType;
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

	void Component::setComponentType(glm::i32 type)
	{
		mComponentType = type;
	}
}
