#ifndef _BASIC_ELEMENT_H_
#define _BASIC_ELEMENT_H_

#include "Flag.h"

namespace ai
{
	class ENGINE_API BasicElement
	{
	public:
		BasicElement(u32 id);
		BasicElement(u32 id, const Flag& flag);

		virtual ~BasicElement();

		inline void SetId(u32 id);
		inline void SetFlag(const Flag& flag);

		inline u32 GetId() const;
		inline const Flag& GetFlag() const;

	protected:
		Flag mFlag;
		u32 mId;
	};
}

#endif