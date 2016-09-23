#include "BasicComponent.h"

namespace ai
{
	BasicComponent::BasicComponent()
		: mType(-1)
	{
	}

	BasicComponent::BasicComponent(i32 type)
		: mType(type)
	{
	}

	BasicComponent::BasicComponent(i32 type, const Flag& flag)
		: mFlag(flag)
		, mType(type)
	{
	}

	BasicComponent::BasicComponent(const Flag& flag)
		: mFlag(flag)
		, mType(-1)
	{
	}

	BasicComponent::~BasicComponent()
	{
	}

	const Flag& BasicComponent::GetFlag() const
	{
		return mFlag;
	}

	i32 BasicComponent::GetType() const
	{
		return mType;
	}

	void BasicComponent::SetFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	void BasicComponent::SetType(i32 type)
	{
		mType = type;
	}
}
