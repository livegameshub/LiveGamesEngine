#include "Flag.h"

namespace ai
{
	Flag::Flag()
		: mValue(0)
	{
	}

	Flag::Flag(glm::u32 value)
		: mValue(value)
	{
	}

	void Flag::add(glm::u32 value)
	{
		mValue |= value;
	}

	void Flag::remove(glm::u32 value)
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

	bool Flag::isSet(glm::u32 flag) const
	{
		return (mValue & flag) == flag;
	}

	Flag::operator glm::u32() const
	{
		return mValue;
	}

	void Flag::reset()
	{
		mValue = 0;
	}
}
