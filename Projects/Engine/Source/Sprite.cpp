#include "Sprite.h"

namespace lg
{
	Sprite::Sprite(glm::u32 id, const glm::vec2& size)
		: MeshRenderer(id, SPRITE_NODE)
		, mSize(size)
	{
	}

	Sprite::~Sprite()
	{
	}

	const glm::vec2& Sprite::getSize() const
	{
		return mSize;
	}
}
