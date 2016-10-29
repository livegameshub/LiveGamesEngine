#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "MeshRenderer.h"

namespace lg
{
	class ENGINE_API Sprite : public MeshRenderer
	{
	public:
		Sprite(glm::u32 id, const glm::vec2& size);
		~Sprite();

		const glm::vec2& getSize() const;

	private:
		glm::vec2 mSize;
	};
}

#endif // _SPRITE_H_
