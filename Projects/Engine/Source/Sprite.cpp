#include "Sprite.h"

namespace lg
{
	Sprite::Sprite(glm::u32 id)
		: Renderable(id, SPRITE_NODE)
	{
	}

	Sprite::~Sprite()
	{
	}
}
