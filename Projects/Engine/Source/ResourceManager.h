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

		const std::map<glm::u32, BasicResource*>& getAllResources() const;

		void loadAllResources();
		void unloadAllResources();

		static void load(BasicResource* resource);
		static void unload(BasicResource* resource);

		static ResourceManager& GetInstance();

	private:
		std::map<glm::u32, BasicResource*> mAllResources;
		std::vector<BasicResource*> mPendingResources;
	};
}

#endif
