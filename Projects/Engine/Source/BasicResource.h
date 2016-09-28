#ifndef _BASIC_RESOURCE_H_
#define _BASIC_RESOURCE_H_

#include "BasicElement.h"

namespace ai
{
	class ENGINE_API BasicResource : public BasicElement
	{
	public:
		BasicResource(glm::u32 id);
		BasicResource(glm::u32 id, const Flag& flag);
		BasicResource(glm::u32 id, const std::string& file);
		
		virtual ~BasicResource();

		std::string GetResourceFile() const;
		void SetResourceFile(const std::string& file);

		glm::u32 GetReferencesCounter() const;

		bool Unload();
		bool Load();

	protected:
		std::string mResourceFile;

	private:
		virtual bool Create() = 0;
		virtual bool Release() = 0;

		glm::u32 mReferencesCounter;
	};
}

#endif
