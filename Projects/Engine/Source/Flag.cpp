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

	void Flag::Add(glm::u32 value)
	{
		mValue |= value;
	}

	void Flag::Remove(glm::u32 value)
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

	bool Flag::IsSet(glm::u32 flag) const
	{
		return (mValue & flag) == flag;
	}

	Flag::operator glm::u32() const
	{
		return mValue;
	}

	void Flag::Reset()
	{
		mValue = 0;
	}
}
