#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "ResourceContainer.h"
#include "Material.h"

namespace lg
{
	class Mesh;
	class DiffuseMaterial;
	class Program;
	class Resource;
	class Shader;
	class Texture;

	class ENGINE_API Resources
	{
	public:
		void release();
		void process();

		void load(Resource* resource);
		void unload(Resource* resource);

		void add(Resource* resource);
		void remove(u32 id);

		/* meshes */
		// TODO
		// move this method somewhere else
		Mesh* createMesh(u32 id, const vec2& startPoint, const vec2& size, const vec2& textureSize);

		/* materials */
		template <class T> T* create(u32 id);
		template <class T> T* create(u32 id, const Flag& flag);
		template <class T> T* create(u32 id, const string& file);
		template <class T> T* getResource(u32 id) const;

		const map<u32, Resource*>& getResources() const;

		static u32 getNextId();
		static Resources& instance();

	private:
		map<u32, Resource*> mAllResources;
		vector<ResourceContainer> mPendingItems;
	};

	/* template class methods - begin */
	template <class T>
	T* Resources::create(u32 id)
	{
		assert(getResource<T>(id) == nullptr);
		T* resource = new T(id);

		add(resource);

		return resource;
	}

	template <class T>
	T* Resources::create(u32 id, const Flag& flag)
	{
		assert(getResource<T>(id) == nullptr);
		T* resource = new T(id, flag);

		add(resource);

		return resource;
	}

	template <class T>
	T* Resources::create(u32 id, const string& file)
	{
		assert(getResource<T>(id) == nullptr);
		T* resource = new T(id, file);

		add(resource);

		return resource;
	}

	template <class T>
	T* Resources::getResource(u32 id) const
	{
		auto it = mAllResources.find(id);

		if (it == mAllResources.end())
		{
			return nullptr;
		}

		return static_cast<T*>(it->second);
	}
	/* template class methods - end */
}

#endif // _RESOURCES_H_
