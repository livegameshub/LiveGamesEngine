#ifndef _BASIC_RESOURCE_H_
#define _BASIC_RESOURCE_H_

#include "BasicElement.h"

namespace ai
{
	class BasicResource : public BasicElement
	{
	public:
		ENGINE_API BasicResource(u32 id);
		
		ENGINE_API virtual ~BasicResource();

		ENGINE_API bool Load();
		ENGINE_API bool Unload();

		ENGINE_API inline u32 GetReferencesCounter() const;

		ENGINE_API inline std::string GetResourceFile() const;
		ENGINE_API inline void SetResourceFile(const std::string& file);

	private:
		virtual bool Create() = 0;
		virtual bool Release() = 0;

		std::string mResourceFile;
		u32 mReferencesCounter;
	};
}

#endif
