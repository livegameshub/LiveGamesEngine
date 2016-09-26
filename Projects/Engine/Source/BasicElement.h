#ifndef _BASIC_ELEMENT_H_
#define _BASIC_ELEMENT_H_

#include "Flag.h"

namespace ai
{
	class ENGINE_API BasicElement
	{
	public:
		BasicElement(glm::u32 id);
		BasicElement(glm::u32 id, const Flag& flag);

		virtual ~BasicElement();

		inline void SetId(glm::u32 id);
		inline void SetFlag(const Flag& flag);

		inline glm::u32 GetId() const;
		inline const Flag& GetFlag() const;

	protected:
		glm::u32 mId;
		Flag mFlag;
	};
}

#endif