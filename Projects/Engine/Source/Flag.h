#ifndef _FLAG_H_
#define _FLAG_H_

#include "EngineUtil.h"

namespace ai
{
	struct ENGINE_API Flag
	{
		Flag();
		Flag(glm::u32 value);

		void Add(glm::u32 value);
		void Remove(glm::u32 value);

		Flag operator+(const Flag& flag) const;
		Flag operator-(const Flag& flag) const;

		Flag& operator+=(const Flag& flag);
		Flag& operator-=(const Flag& flag);

		operator glm::u32() const;

		bool IsSet(glm::u32 flag) const;

		void Reset();

	private:
		glm::u32 mValue;
	};
}

#endif
