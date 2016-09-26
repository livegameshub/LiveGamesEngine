#include "BasicElement.h"

namespace ai
{
	BasicElement::BasicElement(glm::u32 id)
		: mId(id)
	{
	}

	BasicElement::BasicElement(glm::u32 id, const Flag& flag)
		: mId(id)
		, mFlag(flag)
	{
	}

	BasicElement::~BasicElement()
	{
	}

	void BasicElement::SetId(glm::u32 id)
	{
		mId = id;
	}

	void BasicElement::SetFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	glm::u32 BasicElement::GetId() const
	{
		return mId;
	}

	const Flag& BasicElement::GetFlag() const
	{
		return mFlag;
	}
}
