#include "Font.h"

namespace lg
{
	Font::Font(u32 id, const string& file)
		: Resource(id, file)
	{
	}

	Font::~Font()
	{
	}

	bool Font::create()
	{
		return true;
	}

	bool Font::release()
	{
		return true;
	}
}
