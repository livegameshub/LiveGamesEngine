#include "Resources.h"
#include "ShaderResource.h"
#include "ProgramResource.h"
#include "MeshResource.h"
#include "DiffuseMaterial.h"

namespace ai
{
	void Resources::flushPendingItems()
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

	void Resources::load(BasicResource* resource)
	{
		assert(resource != nullptr);

		mPendingItems.push_back(BasicResourceContainer(resource, BasicResourceContainer::LOAD_ACTION));
	}

	void Resources::unload(BasicResource* resource)
	{
		assert(resource != nullptr);

		mPendingItems.push_back(BasicResourceContainer(resource, BasicResourceContainer::UNLOAD_ACTION));
	}

	void Resources::release()
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

	void Resources::removeResource(glm::u32 id)
	{
		auto it = mAllResources.find(id);

		assert(it != mAllResources.end());
	
		it->second->unload();

		mAllResources.erase(it);
	}

	void Resources::addResource(BasicResource* resource)
	{
		assert(resource != nullptr);
		assert(mAllResources.find(resource->getId()) == mAllResources.end());

		mAllResources.insert({ resource->getId(), resource });	
	}

	BasicResource* Resources::getResource(glm::u32 id) const
	{
		auto it = mAllResources.find(id);

		if (it == mAllResources.end())
		{
			return nullptr;
		}

		return it->second;
	}

	BasicResource* Resources::operator[](glm::u32 id) const
	{
		return getResource(id);
	}

	const std::map<glm::u32, BasicResource*>& Resources::getAllResources() const
	{
		return mAllResources;
	}

	ProgramResource* Resources::createProgram(glm::u32 id, const std::vector<ShaderResource*> shaders)
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

	ShaderResource* Resources::createShader(glm::u32 id, glm::u32 type, const std::string& file)
	{
		assert(getResource(id) == nullptr);

		ShaderResource* shader = new ShaderResource(id, type, file);

		addResource(shader);

		return shader;
	}

	BasicMaterial* Resources::createMaterial(glm::u32 id, ProgramResource* program, const glm::vec3& diffuse, const Flag& flag)
	{
		assert(getResource(id) == nullptr);

		BasicMaterial* material = new BasicMaterial(id, diffuse, flag);
		material->setProgram(program);

		addResource(material);

		return material;
	}

	DiffuseMaterial* Resources::createMaterial(glm::u32 id, ProgramResource* program, const glm::vec3& diffuse, const glm::vec3& specular, glm::f32 shininess, const Flag& flag)
	{
		assert(getResource(id) == nullptr);

		DiffuseMaterial* material = new DiffuseMaterial(id, diffuse, specular, shininess, flag);
		material->setProgram(program);

		addResource(material);

		return material;
	}

	MeshResource* Resources::createMesh(glm::u32 id, const std::string& file)
	{
		assert(getResource(id) == nullptr);

		MeshResource* mesh = new MeshResource(id, file);

		addResource(mesh);

		return mesh;
	}

	Resources& Resources::getInstance()
	{
		static Resources instance;

		return instance;
	}
}
