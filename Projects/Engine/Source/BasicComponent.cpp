#include "BasicComponent.h"

namespace ai
{
	BasicComponent::BasicComponent()
		: mIsEnabled(true)
		, mComponentType(-1)
	{
	}

	BasicComponent::BasicComponent(glm::i32 type)
		: mIsEnabled(true)
		, mComponentType(type)
	{
	}

	BasicComponent::BasicComponent(glm::i32 type, const Flag& flag)
		: mIsEnabled(true)
		, mFlag(flag)
		, mComponentType(type)
	{
	}

	BasicComponent::BasicComponent(const Flag& flag)
		: mIsEnabled(true)
		, mFlag(flag)
		, mComponentType(-1)
	{
	}

	BasicComponent::~BasicComponent()
	{
	}

	const Flag& BasicComponent::getFlag() const
	{
		return mFlag;
	}

	glm::i32 BasicComponent::getComponentType() const
	{
		return mComponentType;
	}

	void BasicComponent::setEnabled(bool value)
	{
		mIsEnabled = value;
	}

	bool BasicComponent::isEnabled() const
	{
		return mIsEnabled;
	}

	void BasicComponent::setFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	void BasicComponent::setComponentType(glm::i32 type)
	{
		mComponentType = type;
	}
}
