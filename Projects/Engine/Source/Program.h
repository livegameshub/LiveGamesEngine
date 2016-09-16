#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "BasicResource.h"

namespace ai
{
	class ENGINE_API Program : public BasicResource
	{
	public:
		enum AttributeIndex : u32
		{
			POSITION_INDEX,
			TEXTURE_INDEX,
			NORMAL_INDEX,
			COUNT
		};

		Program(u32 id);
		~Program();

	private:

	};
}

#endif
