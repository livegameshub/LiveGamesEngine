#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Flag.h"

namespace lg
{
	class ENGINE_API Object
	{
	public:
		Object(glm::u32 id);
		Object(glm::u32 id, const Flag& flag);

		virtual ~Object();

		void setId(glm::u32 id);
		void setFlag(const Flag& flag);
		
		const Flag& getFlag() const;
		glm::u32 getId() const;

		Flag& getFlag();
		
	protected:
		glm::u32 mId;
		Flag mFlag;
	};
}

#endif // _OBJECT_H_