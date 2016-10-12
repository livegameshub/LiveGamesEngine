#ifndef _BASIC_RESOURCE_H_
#define _BASIC_RESOURCE_H_

#include "BasicElement.h"

namespace ai
{
	class ENGINE_API BasicResource : public BasicElement
	{
	public:
		enum BasicResourceFlag : glm::u32
		{
			IS_UNLOADED = 1
		};

		BasicResource(glm::u32 id);
		BasicResource(glm::u32 id, const Flag& flag);
		BasicResource(glm::u32 id, const std::string& file);
		
		virtual ~BasicResource();

		std::string getResourceFile() const;
		void setResourceFile(const std::string& file);

		glm::u32 getReferencesCounter() const;

		bool unload();
		bool load();

	protected:
		std::string mResourceFile;

	private:
		virtual bool create() = 0;
		virtual bool release() = 0;

		glm::u32 mReferencesCounter;
	};
}

#endif // _BASIC_RESOURCE_H_
