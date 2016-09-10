#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include "Flag.h"

namespace ai
{
	class ENGINE_API BaseObject
	{
	public:
		BaseObject(u32 id);
		BaseObject(u32 id, const Flag& flag);

		virtual ~BaseObject();

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