#include "Random.h"

namespace ai
{
	Random::Random()
		: mValue(0)
	{
	}

	void Random::Seed()
	{
		srand(static_cast<u32>(time(0)));
	}

	u32 Random::GetRandomInt(u32 max)
	{
		mValue = rand() % (max + 1);

		return mValue;
	}

	u32 Random::GetRandomInt(u32 min, u32 max)
	{
		mValue = rand() % (max - min + 1) + min;

		return mValue;
	}

	u32 Random::GetValue() const
	{
		return mValue;
	}

	Random::operator u32() const
	{
		return mValue;
	}
}
