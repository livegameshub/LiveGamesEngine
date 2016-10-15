#include "ResourceManager.h"
#include "ShaderResource.h"
#include "ProgramResource.h"
#include "MeshResource.h"
#include "BasicMaterialResource.h"

namespace ai
{
	void ResourceManager::flushPendingItems()
	{
		/* we use the classic for because the collection can grow */

		for (int i = 0; i < mPendingItems.size(); i++)
		{
			const BasicResourceContainer& item = mPendingItems[i];

			if (item.flag.isSet(BasicResourceContainer::LOAD_ACTION))
			{
				item.resource->load();
			}
			else if (item.flag.isSet(BasicResourceContainer::UNLOAD_ACTION))
			{
				item.resource->unload();
			}
		}

		mPendingItems.clear();
	}

	void ResourceManager::load(BasicResource* resource)
	{
		assert(resource != nullptr);

		mPendingItems.push_back(BasicResourceContainer(resource, BasicResourceContainer::LOAD_ACTION));
	}

	void ResourceManager::unload(BasicResource* resource)
	{
		assert(resource != nullptr);

		mPendingItems.push_back(BasicResourceContainer(resource, BasicResourceContainer::UNLOAD_ACTION));
	}

	void ResourceManager::release()
	{
		flushPendingItems();

		for (auto it : mAllResources)
		{
			BasicResource* resource = it.second;

			assert(resource != nullptr);
			assert(resource->getReferencesCounter() == 0);

			delete resource;
			resource = nullptr;
		}
	}

	void ResourceManager::removeResource(glm::u32 id)
	{
		auto it = mAllResources.find(id);

		assert(it != mAllResources.end());
	
		it->second->unload();

		mAllResources.erase(it);
	}

	void ResourceManager::addResource(BasicResource* resource)
	{
		assert(resource != nullptr);
		assert(mAllResources.find(resource->getId()) == mAllResources.end());

		mAllResources.insert({ resource->getId(), resource });	
	}

	BasicResource* ResourceManager::getResource(glm::u32 id) const
	{
		auto it = mAllResources.find(id);

		if (it == mAllResources.end())
		{
			return nullptr;
		}

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

	ProgramResource* ResourceManager::createProgram(glm::u32 id, const std::vector<ShaderResource*> shaders)
	{
		assert(getResource(id) == nullptr);

		ProgramResource* program = new ProgramResource(id);

		for (auto shader : shaders)
		{
			program->addShader(shader);
		}

		addResource(program);

		return program;
	}

	ShaderResource* ResourceManager::createShader(glm::u32 id, glm::u32 type, const std::string& file)
	{
		assert(getResource(id) == nullptr);

		ShaderResource* shader = new ShaderResource(id, type, file);

		addResource(shader);

		return shader;
	}

	BasicMaterialResource* ResourceManager::createMaterial(glm::u32 id, ProgramResource* program, const glm::vec3& diffuse, const Flag& flag)
	{
		assert(getResource(id) == nullptr);

		BasicMaterialResource* material = new BasicMaterialResource(id, diffuse, flag);
		material->setProgram(program);

		addResource(material);

		return material;
	}

	MeshResource* ResourceManager::createMesh(glm::u32 id, const std::string& file)
	{
		assert(getResource(id) == nullptr);

		MeshResource* mesh = new MeshResource(id, file);

		addResource(mesh);

		return mesh;
	}

	ResourceManager& ResourceManager::getInstance()
	{
		static ResourceManager instance;

		return instance;
	}
}
