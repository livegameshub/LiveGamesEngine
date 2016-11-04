#ifndef _FONT_CHARACTER_H_
#define _FONT_CHARACTER_H_

#include "EngineUtil.h"

namespace lg
{
	struct ENGINE_API FontCharacter
	{
		ivec2 size;	// Size of character
		ivec2 bearing; // Offset from baseline to left/top of glyph	
		u32 advance;   // Offset to advance to next glyph
	};
}

#endif // _FONT_CHARACTER_H_
