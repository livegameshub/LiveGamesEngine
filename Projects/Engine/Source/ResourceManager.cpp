#include "ResourceManager.h"

namespace ai
{
	void ResourceManager::Release()
	{
		for (auto it : mResources)
		{
			BasicResource* resource = it.second;

			assert(resource != nullptr);

			resource->Unload();

			delete resource;
			resource = nullptr;
		}
	}

	void ResourceManager::RemoveResource(glm::u32 id)
	{
		auto it = mResources.find(id);

		assert(it != mResources.end());
	
		it->second->Unload();

		mResources.erase(it);
	}

	void ResourceManager::AddResource(BasicResource* resource)
	{
		assert(resource != nullptr);

		mResources.insert({ resource->GetId(), resource });	
	}

	BasicResource* ResourceManager::GetResource(glm::u32 id) const
	{
		auto it = mResources.find(id);

		assert(it != mResources.end());
		
		return it->second;
	}

	BasicResource* ResourceManager::operator[](glm::u32 id) const
	{
		return GetResource(id);
	}

	const std::map<glm::u32, BasicResource*>& ResourceManager::GetResources() const
	{
		return mResources;
	}

	ResourceManager& ResourceManager::GetInstance()
	{
		static ResourceManager instance;

		return instance;
	}
}
