#include "BasicElement.h"

namespace ai
{
	BasicElement::BasicElement(u32 id)
		: mId(id)
	{
	}

	BasicElement::BasicElement(u32 id, const Flag& flag)
		: mFlag(flag)
		, mId(id)
	{
	}

	BasicElement::~BasicElement()
	{
	}

	void BasicElement::SetId(u32 id)
	{
		mId = id;
	}

	void BasicElement::SetFlag(const Flag& flag)
	{
		mFlag = flag;
	}

	u32 BasicElement::GetId() const
	{
		return mId;
	}

	const Flag& BasicElement::GetFlag() const
	{
		return mFlag;
	}
}
