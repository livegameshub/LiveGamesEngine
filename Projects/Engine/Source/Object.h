#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Flag.h"

namespace lg
{
	class ENGINE_API Object
	{
	public:
		Object(u32 id);
		Object(u32 id, const Flag& flag);

		virtual ~Object();

		void setId(u32 id);
		void setFlag(const Flag& flag);
		
		const Flag& getFlag() const;
		u32 getId() const;

		Flag& getFlag();
		
	protected:
		u32 mId;
		Flag mFlag;
	};
}

#endif // _OBJECT_H_