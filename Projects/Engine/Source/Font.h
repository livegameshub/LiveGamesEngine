#ifndef _FONT_H_
#define _FONT_H_

#include "Resource.h"

namespace lg
{
	class ENGINE_API Font : public Resource
	{
	public:
		Font(u32 id, const string& file);
		~Font();

	private:
		bool create() override;
		bool release() override;
	};
}

#endif // _FONT_H_
