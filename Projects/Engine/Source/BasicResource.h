#ifndef _BASIC_RESOURCE_H_
#define _BASIC_RESOURCE_H_

#include "BasicElement.h"

namespace ai
{
	class ENGINE_API BasicResource : public BasicElement
	{
	public:
		BasicResource(u32 id);
		BasicResource(u32 id, const Flag& flag);
		BasicResource(u32 id, const std::string& file);
		
		virtual ~BasicResource();

		inline std::string GetResourceFile() const;
		inline void SetResourceFile(const std::string& file);

		inline u32 GetReferencesCounter() const;

		bool Unload();
		bool Load();

	protected:
		std::string mResourceFile;

	private:
		virtual bool Create() = 0;
		virtual bool Release() = 0;

		u32 mReferencesCounter;
	};
}

#endif
