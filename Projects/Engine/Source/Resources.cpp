#include "Resources.h"
#include "Shader.h"
#include "Program.h"
#include "Mesh.h"
#include "DiffuseMaterial.h"
#include "Texture.h"

namespace lg
{
	void Resources::process()
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
		process();

		for (auto it : mAllResources)
		{
			assert(it.second != nullptr);
			assert(it.second->getReferencesCounter() == 0);

			SAFE_DELETE(it.second);
		}
	}

	void Resources::remove(u32 id)
	{
		auto it = mAllResources.find(id);
		assert(it != mAllResources.end());
	
		it->second->unload();

		mAllResources.erase(it);
	}

	void Resources::add(Resource* resource)
	{
		assert(resource != nullptr);
		assert(mAllResources.find(resource->getId()) == mAllResources.end());

		mAllResources.insert({ resource->getId(), resource });	
	}

	const map<u32, Resource*>& Resources::getResources() const
	{
		return mAllResources;
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

		add(mesh);

		return mesh;
	}

	u32 Resources::getNextId()
	{
		static u32 current_id = 0;

		return ++current_id;
	}

	Resources& Resources::instance()
	{
		static Resources instance;

		return instance;
	}
}
