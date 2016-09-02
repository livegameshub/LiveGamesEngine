#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "EngineUtil.h"

namespace ai
{
	struct ENGINE_API Random
	{
		Random();

		inline u32 GetRandomInt(u32 max);
		inline u32 GetRandomInt(u32 min, u32 max);

		inline operator u32() const;

		static void Seed();
	
	private:
		u32 mValue;
	};
}

#endif
