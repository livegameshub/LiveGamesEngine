#include "ResourceManager.h"

namespace ai
{
	void ResourceManager::FlushPendingItems()
	{
		for (glm::u32 i = 0; i < mPendingItems.size(); ++i)
		{
			BasicResource* item = mPendingItems[i];

			if (item->GetFlag().IsSet(BasicResource::IS_UNLOADED))
			{
				item->Load();

				item->GetFlag().Remove(BasicResource::IS_UNLOADED);
			}
			else
			{
				item->Unload();
			}
		}

		mPendingItems.clear();
	}

	void ResourceManager::addPendingItem(BasicResource* resource, bool isUnloaded)
	{
		assert(resource != nullptr);

		if (isUnloaded)
		{
			resource->GetFlag().Add(BasicResource::IS_UNLOADED);
		}

		getInstance().mPendingItems.push_back(resource);
	}

	void ResourceManager::Release()
	{
		FlushPendingItems();

		for (auto it : mAllResources)
		{
			BasicResource* resource = it.second;

			assert(resource != nullptr);
			assert(resource->GetReferencesCounter() == 0);

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

	BasicResource* ResourceManager::getResource(glm::u32 id) const
	{
		auto it = mAllResources.find(id);

		assert(it != mAllResources.end());
		
		return it->second;
	}

	BasicResource* ResourceManager::operator[](glm::u32 id) const
	{
		return getResource(id);
	}

	const std::map<glm::u32, BasicResource*>& ResourceManager::getAllResources() const
	{
		return mAllResources;
	}

	ResourceManager& ResourceManager::getInstance()
	{
		static ResourceManager instance;

		return instance;
	}
}
