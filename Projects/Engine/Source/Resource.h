#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "BasicElement.h"

namespace lg
{
	class ENGINE_API Resource : public BasicElement
	{
	public:
		Resource(glm::u32 id);
		Resource(glm::u32 id, const Flag& flag);
		Resource(glm::u32 id, const std::string& file);
		
		virtual ~Resource();

		const std::string& getResourceFile() const;
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

#endif // _RESOURCE_H_
