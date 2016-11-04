#ifndef _FLAG_H_
#define _FLAG_H_

#include "EngineUtil.h"

namespace lg
{
	struct ENGINE_API Flag
	{
		Flag();
		Flag(u32 value);

		void add(u32 value);
		void remove(u32 value);

		Flag operator+(const Flag& flag) const;
		Flag operator-(const Flag& flag) const;

		Flag& operator+=(const Flag& flag);
		Flag& operator-=(const Flag& flag);

		operator u32() const;

		bool isSet(u32 flag) const;

		void reset();

	private:
		u32 mValue;
	};
}

#endif // _FLAG_H_
