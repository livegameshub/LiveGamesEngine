#ifndef _FLAG_H_
#define _FLAG_H_

#include "EngineUtil.h"

namespace ai
{
	struct ENGINE_API Flag
	{
		Flag();
		Flag(u32 value);

		inline void Add(u32 value);
		inline void Remove(u32 value);

		inline Flag operator+(const Flag& flag) const;
		inline Flag operator-(const Flag& flag) const;

		inline Flag& operator+=(const Flag& flag);
		inline Flag& operator-=(const Flag& flag);

		inline bool IsSet(u32 flag) const;
		inline operator u32() const;

		inline void Reset();

	private:
		u32 mValue;
	};
}

#endif
