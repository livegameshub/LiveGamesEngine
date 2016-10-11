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

	void BasicElement::setId(glm::u32 id)
	{
		mId = id;
	}

	void BasicElement::setFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	glm::u32 BasicElement::getId() const
	{
		return mId;
	}

	const Flag& BasicElement::getFlag() const
	{
		return mFlag;
	}

	Flag& BasicElement::getFlag()
	{
		return mFlag;
	}
}
