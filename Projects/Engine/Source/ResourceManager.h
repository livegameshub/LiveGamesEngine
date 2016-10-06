#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include "BasicResource.h"

namespace ai
{
	class ENGINE_API ResourceManager
	{
	public:
		void Release();
		void FlushPendingItems();

		void RemoveResource(glm::u32 id);
		void AddResource(BasicResource* resource);
		
		BasicResource* getResource(glm::u32 id) const;
		BasicResource* operator[](glm::u32 id) const;

		const std::map<glm::u32, BasicResource*>& getAllResources() const;

		static void addPendingItem(BasicResource* resource, bool isUnloaded);
		static ResourceManager& getInstance();

	private:
		std::map<glm::u32, BasicResource*> mAllResources;
		std::vector<BasicResource*> mPendingItems;
	};
}

#endif
