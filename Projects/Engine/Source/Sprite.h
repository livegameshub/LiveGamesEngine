#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Renderable.h"

namespace lg
{
	class ENGINE_API Sprite : public Renderable
	{
	public:
		Sprite(glm::u32 id);
		~Sprite();

	private:

	};
}

#endif // _SPRITE_H_
