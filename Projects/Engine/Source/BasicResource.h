#ifndef _BASIC_RESOURCE_H_
#define _BASIC_RESOURCE_H_

#include "BasicElement.h"

namespace ai
{
	class ENGINE_API BasicResource : public BasicElement
	{
	public:
		BasicResource(u32 id);
		
		virtual ~BasicResource();

		bool Load();
		bool Unload();

	private:
		virtual bool Create() = 0;
		virtual bool Release() = 0;

		u32 mReferencesCounter;
	};
}

#endif
