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

			SAFE_DELETE(resource);
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

	const std::map<glm::u32, Resource*>& Resources::getAllResources() const
	{
		return mAllResources;
	}

	Program* Resources::createProgram(glm::u32 id, const std::vector<Shader*> shaders)
	{
		assert(getResource<Program>(id) == nullptr);

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
		assert(getResource<Shader>(id) == nullptr);

		Shader* shader = new Shader(id, type, file);

		addResource(shader);

		return shader;
	}

	Mesh* Resources::createMesh(glm::u32 id, const std::string& file)
	{
		assert(getResource<Mesh>(id) == nullptr);

		Mesh* mesh = new Mesh(id, file);

		addResource(mesh);

		return mesh;
	}

	Mesh* Resources::createMesh(glm::u32 id, glm::u32 primitive, glm::u32 drawType, const Flag& flag)
	{
		assert(getResource<Mesh>(id) == nullptr);

		Mesh* mesh = new Mesh(id, primitive, drawType, flag);

		addResource(mesh);

		return mesh;
	}

	Mesh* Resources::createMesh(glm::u32 id, const glm::vec2& startPoint, const glm::vec2& size, const glm::vec2& textureSize)
	{
		assert(getResource<Mesh>(id) == nullptr);

		Mesh* mesh = new Mesh(id, Mesh::TRIANGLES, Mesh::STATIC_DRAW, Mesh::USE_TEXTURES);

		MeshData& data = mesh->getData();

		data.addVertex(glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f), glm::vec2((startPoint.x + size.x) / textureSize.x, (startPoint.y + size.y) / textureSize.y));
		data.addVertex(glm::vec3(size.x * 0.5f, -(size.y * 0.5f), 0.0f), glm::vec2((startPoint.x + size.x) / textureSize.x, startPoint.y / textureSize.y));
		data.addVertex(glm::vec3(-(size.x * 0.5f), -(size.y * 0.5f), 0.0f), glm::vec2(startPoint.x / textureSize.x, startPoint.y / textureSize.y));
		data.addVertex(glm::vec3(-(size.x * 0.5f), size.y * 0.5f, 0.0f), glm::vec2(startPoint.x / textureSize.x, (startPoint.y + size.y) / textureSize.y));
			 
		data.addTriangle(0, 1, 3);
		data.addTriangle(1, 2, 3);

		addResource(mesh);

		return mesh;
	}

	Texture* Resources::createTexture(glm::u32 id, const std::string& file, bool generateMipmaps)
	{
		assert(getResource<Texture>(id) == nullptr);

		Texture* texture = new Texture(id, file, generateMipmaps);

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
