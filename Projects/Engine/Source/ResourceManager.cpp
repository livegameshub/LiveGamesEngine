#include "ResourceManager.h"
#include "ShaderResource.h"

namespace ai
{
	void ResourceManager::flushPendingItems()
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

		mPendingItems.push_back(resource);
	}

	void ResourceManager::release()
	{
		flushPendingItems();

		for (auto it : mAllResources)
		{
			BasicResource* resource = it.second;

			assert(resource != nullptr);
			assert(resource->GetReferencesCounter() == 0);

			delete resource;
			resource = nullptr;
		}
	}

	void ResourceManager::removeResource(glm::u32 id)
	{
		auto it = mAllResources.find(id);

		assert(it != mAllResources.end());
	
		it->second->Unload();

		mAllResources.erase(it);
	}

	void ResourceManager::addResource(BasicResource* resource)
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

	ProgramResource* ResourceManager::createProgram(glm::u32 id, ShaderResource* vertex, ShaderResource* fragment, const std::vector<std::string>& uniforms)
	{
		ProgramResource* program = new ProgramResource(id);
		program->AddShader(vertex);
		program->AddShader(fragment);
		program->AddUniforms(uniforms);

		addResource(program);

		return program;
	}

	ShaderResource* ResourceManager::createShader(glm::u32 id, glm::u32 type, const std::string& file)
	{
		ShaderResource* shader = new ShaderResource(id, type, file);

		addResource(shader);

		return shader;
	}

	MaterialResource* ResourceManager::createMaterial(glm::u32 id, ProgramResource* program, const glm::vec3& diffuse, const Flag& flag)
	{
		MaterialResource* material = new MaterialResource(id, diffuse, flag);
		material->SetProgram(program);

		addResource(material);

		return material;
	}

	MeshResource* ResourceManager::createMesh(glm::u32 id, const std::string& file)
	{
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
