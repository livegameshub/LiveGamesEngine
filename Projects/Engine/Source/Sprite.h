#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Node.h"

namespace lg
{
	class ENGINE_API Sprite : public Node
	{
	public:
		Sprite(u32 id, i32 type);

		virtual ~Sprite();

		void setSize(const vec2& size);
		const vec2& getSize() const;

	private:
		vec2 mSize;
	};
}

#endif // _SPRITE_H_
