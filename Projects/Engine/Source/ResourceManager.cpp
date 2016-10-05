#include "ResourceManager.h"

namespace ai
{
	void ResourceManager::loadAllResources()
	{
		for (glm::u32 i = mPendingResources.size(); i > 0; --i)
		{
			mPendingResources[i - 1]->Load();
			mPendingResources.pop_back();
		}
	}

	void ResourceManager::unloadAllResources()
	{	
	}

	void ResourceManager::load(BasicResource* resource)
	{
		assert(resource != nullptr);

		GetInstance().mPendingResources.push_back(resource);
	}

	void ResourceManager::unload(BasicResource* resource)
	{	
	}

	void ResourceManager::Release()
	{
		for (auto it : mAllResources)
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
		auto it = mAllResources.find(id);

		assert(it != mAllResources.end());
	
		it->second->Unload();

		mAllResources.erase(it);
	}

	void ResourceManager::AddResource(BasicResource* resource)
	{
		assert(resource != nullptr);

		mAllResources.insert({ resource->GetId(), resource });	
	}

	BasicResource* ResourceManager::GetResource(glm::u32 id) const
	{
		auto it = mAllResources.find(id);

		assert(it != mAllResources.end());
		
		return it->second;
	}

	BasicResource* ResourceManager::operator[](glm::u32 id) const
	{
		return GetResource(id);
	}

	const std::map<glm::u32, BasicResource*>& ResourceManager::getAllResources() const
	{
		return mAllResources;
	}

	ResourceManager& ResourceManager::GetInstance()
	{
		static ResourceManager instance;

		return instance;
	}
}
