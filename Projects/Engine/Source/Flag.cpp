#include "Flag.h"

namespace lg
{
	Flag::Flag()
		: mValue(0)
	{
	}

	Flag::Flag(u32 value)
		: mValue(value)
	{
	}

	void Flag::add(u32 value)
	{
		mValue |= value;
	}

	void Flag::remove(u32 value)
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

	Flag& Flag::operator+=(const Flag& flag)
	{
		mValue |= flag;

		return *this;
	}

	Flag& Flag::operator-=(const Flag& flag)
	{
		mValue &= ~flag;

		return *this;
	}

	bool Flag::isSet(u32 flag) const
	{
		return (mValue & flag) == flag;
	}

	Flag::operator u32() const
	{
		return mValue;
	}

	void Flag::reset()
	{
		mValue = 0;
	}
}
