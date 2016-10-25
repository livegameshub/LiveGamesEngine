#include "Resources.h"
#include "Shader.h"
#include "Program.h"
#include "Mesh.h"
#include "DiffuseMaterial.h"
#include "Texture.h"

namespace lg
{
	void Resources::processPendingItems()
	{
		/* we use the classic for because the collection can grow */

		for (int i = 0; i < mPendingItems.size(); i++)
		{
			const ResourceContainer& item = mPendingItems[i];

			if (item.flag.isSet(ResourceContainer::LOAD_ACTION))
			{
				item.resource->load();
			}
			else if (item.flag.isSet(ResourceContainer::UNLOAD_ACTION))
			{
				item.resource->unload();
			}
		}

		mPendingItems.clear();
	}

	void Resources::load(Resource* resource)
	{
		assert(resource != nullptr);

		mPendingItems.push_back(ResourceContainer(resource, ResourceContainer::LOAD_ACTION));
	}

	void Resources::unload(Resource* resource)
	{
		assert(resource != nullptr);

		mPendingItems.push_back(ResourceContainer(resource, ResourceContainer::UNLOAD_ACTION));
	}

	void Resources::release()
	{
		processPendingItems();

		for (auto it : mAllResources)
		{
			Resource* resource = it.second;

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

	void Resources::addResource(Resource* resource)
	{
		assert(resource != nullptr);
		assert(mAllResources.find(resource->getId()) == mAllResources.end());

		mAllResources.insert({ resource->getId(), resource });	
	}

	Resource* Resources::getResource(glm::u32 id) const
	{
		auto it = mAllResources.find(id);

		if (it == mAllResources.end())
		{
			return nullptr;
		}

		return it->second;
	}

	Resource* Resources::operator[](glm::u32 id) const
	{
		return getResource(id);
	}

	const std::map<glm::u32, Resource*>& Resources::getAllResources() const
	{
		return mAllResources;
	}

	Program* Resources::createProgram(glm::u32 id, const std::vector<Shader*> shaders)
	{
		assert(getResource(id) == nullptr);

		Program* program = new Program(id);

		for (auto shader : shaders)
		{
			program->addShader(shader);
		}

		addResource(program);

		return program;
	}

	Shader* Resources::createShader(glm::u32 id, glm::u32 type, const std::string& file)
	{
		assert(getResource(id) == nullptr);

		Shader* shader = new Shader(id, type, file);

		addResource(shader);

		return shader;
	}

	Material* Resources::createMaterial(glm::u32 id, Program* program, const glm::vec3& diffuse)
	{
		assert(getResource(id) == nullptr);

		Material* material = new Material(id, diffuse);
		material->setProgram(program);

		addResource(material);

		return material;
	}

	DiffuseMaterial* Resources::createMaterial(glm::u32 id, Program* program, Texture* texture, const glm::vec3& diffuse, const Flag& flag)
	{
		assert(getResource(id) == nullptr);

		DiffuseMaterial* material = new DiffuseMaterial(id, diffuse, flag);
		material->setProgram(program);

		if (texture)
		{
			// if we have a texture assign it
			material->setDiffuseTexture(texture);
		}

		addResource(material);

		return material;
	}

	DiffuseMaterial* Resources::createMaterial(glm::u32 id, Program* program, Texture* texture, const glm::vec3& diffuse, const glm::vec3& specular, glm::f32 shininess, const Flag& flag)
	{
		assert(getResource(id) == nullptr);

		DiffuseMaterial* material = new DiffuseMaterial(id, diffuse, specular, shininess, flag);
		material->setProgram(program);

		if (texture)
		{
			// if we have a texture assign it
			material->setDiffuseTexture(texture);
		}

		addResource(material);

		return material;
	}

	Mesh* Resources::createMesh(glm::u32 id, const std::string& file)
	{
		assert(getResource(id) == nullptr);

		Mesh* mesh = new Mesh(id, file);

		addResource(mesh);

		return mesh;
	}

	Mesh* Resources::createMesh(glm::u32 id, glm::u32 primitive, glm::u32 drawType, const Flag& flag)
	{
		assert(getResource(id) == nullptr);

		Mesh* mesh = new Mesh(id, primitive, drawType, flag);

		addResource(mesh);

		return mesh;
	}

	Texture* Resources::createTexture(glm::u32 id, const std::string& file)
	{
		assert(getResource(id) == nullptr);

		Texture* texture = new Texture(id, file);

		addResource(texture);

		return texture;
	}

	glm::u32 Resources::getNextAvailableId()
	{
		static glm::u32 current_id = 0;

		return ++current_id;
	}

	Resources& Resources::getInstance()
	{
		static Resources instance;

		return instance;
	}
}
