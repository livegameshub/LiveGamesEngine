#include "BasicComponent.h"

namespace ai
{
	BasicComponent::BasicComponent()
		: mIsEnabled(true)
		, mComponentType(-1)
	{
	}

	BasicComponent::BasicComponent(i32 type)
		: mIsEnabled(true)
		, mComponentType(type)
	{
	}

	BasicComponent::BasicComponent(i32 type, const Flag& flag)
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

	const Flag& BasicComponent::GetFlag() const
	{
		return mFlag;
	}

	i32 BasicComponent::GetComponentType() const
	{
		return mComponentType;
	}

	void BasicComponent::SetEnabled(bool value)
	{
		mIsEnabled = value;
	}

	bool BasicComponent::IsEnabled() const
	{
		return mIsEnabled;
	}

	void BasicComponent::SetFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	void BasicComponent::SetComponentType(i32 type)
	{
		mComponentType = type;
	}
}
