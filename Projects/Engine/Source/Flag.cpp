#include "Flag.h"

namespace ai
{
	Flag::Flag()
		: mValue(0)
	{
	}

	Flag::Flag(u32 value)
		: mValue(value)
	{
	}

	void Flag::Add(u32 value)
	{
		mValue |= value;
	}

	void Flag::Remove(u32 value)
	{
		mValue &= ~value;
	}

	Flag Flag::operator+(const Flag& flag) const
	{
		Flag new_flag(mValue | flag);

		return new_flag;
	}

	Flag Flag::operator-(const Flag& flag) const
	{
		Flag new_flag(mValue & ~flag);

		return new_flag;
	}

	bool Flag::IsSet(u32 flag) const
	{
		return (mValue & flag) == flag;
	}

	Flag::operator u32() const
	{
		return mValue;
	}

	void Flag::Reset()
	{
		mValue = 0;
	}
}
