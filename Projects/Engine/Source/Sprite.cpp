#include "Sprite.h"

namespace lg
{
	Sprite::Sprite(u32 id, i32 type)
	{
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::setSize(const vec2& size)
	{
		mSize = size;
	}

	const vec2& Sprite::getSize() const
	{
		return mSize;
	}
}
