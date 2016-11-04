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
			assert(it.second != nullptr);
			assert(it.second->getReferencesCounter() == 0);

			SAFE_DELETE(it.second);
		}
	}

	void Resources::removeResource(u32 id)
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

	const map<u32, Resource*>& Resources::getAllResources() const
	{
		return mAllResources;
	}

	Program* Resources::createProgram(u32 id, const vector<Shader*> shaders)
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

	Shader* Resources::createShader(u32 id, u32 type, const string& file)
	{
		assert(getResource<Shader>(id) == nullptr);

		Shader* shader = new Shader(id, type, file);

		addResource(shader);

		return shader;
	}

	Mesh* Resources::createMesh(u32 id, const string& file)
	{
		assert(getResource<Mesh>(id) == nullptr);

		Mesh* mesh = new Mesh(id, file);

		addResource(mesh);

		return mesh;
	}

	Mesh* Resources::createMesh(u32 id, u32 primitive, u32 drawType, const Flag& flag)
	{
		assert(getResource<Mesh>(id) == nullptr);

		Mesh* mesh = new Mesh(id, primitive, drawType, sizeof(vec3), flag);

		addResource(mesh);

		return mesh;
	}

	Mesh* Resources::createMesh(u32 id, const vec2& startPoint, const vec2& size, const vec2& textureSize)
	{
		assert(getResource<Mesh>(id) == nullptr);

		Mesh* mesh = new Mesh(id, Mesh::TRIANGLES, Mesh::STATIC_DRAW, sizeof(vec2), Mesh::USE_TEXTURES);

		MeshData& data = mesh->getData();

		data.addVertex(vec2(size.x * 0.5f, size.y * 0.5f), vec2((startPoint.x + size.x) / textureSize.x, (startPoint.y + size.y) / textureSize.y));
		data.addVertex(vec2(size.x * 0.5f, -(size.y * 0.5f)), vec2((startPoint.x + size.x) / textureSize.x, startPoint.y / textureSize.y));
		data.addVertex(vec2(-(size.x * 0.5f), -(size.y * 0.5f)), vec2(startPoint.x / textureSize.x, startPoint.y / textureSize.y));
		data.addVertex(vec2(-(size.x * 0.5f), size.y * 0.5f), vec2(startPoint.x / textureSize.x, (startPoint.y + size.y) / textureSize.y));
			 
		data.addTriangle(0, 1, 3);
		data.addTriangle(1, 2, 3);

		addResource(mesh);

		return mesh;
	}

	Texture* Resources::createTexture(u32 id, const string& file, bool generateMipmaps)
	{
		assert(getResource<Texture>(id) == nullptr);

		Texture* texture = new Texture(id, file, generateMipmaps);

		addResource(texture);

		return texture;
	}

	u32 Resources::getNextAvailableId()
	{
		static u32 current_id = 0;

		return ++current_id;
	}

	Resources& Resources::getInstance()
	{
		static Resources instance;

		return instance;
	}
}
