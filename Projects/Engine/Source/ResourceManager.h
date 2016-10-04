#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include "BasicResource.h"

namespace ai
{
	class ENGINE_API ResourceManager
	{
	public:
		void Release();
		void RemoveResource(glm::u32 id);
		void AddResource(BasicResource* resource);
		
		BasicResource* GetResource(glm::u32 id) const;
		BasicResource* operator[](glm::u32 id) const;

		const std::map<glm::u32, BasicResource*>& GetResources() const;

		static ResourceManager& GetInstance();

	private:
		std::map<glm::u32, BasicResource*> mResources;
	};
}

#endif
