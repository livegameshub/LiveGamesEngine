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

#endif