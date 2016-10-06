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

		void SetId(glm::u32 id);
		void SetFlag(const Flag& flag);
		
		const Flag& GetFlag() const;
		glm::u32 GetId() const;

		Flag& GetFlag();
		
	protected:
		glm::u32 mId;
		Flag mFlag;
	};
}

#endif