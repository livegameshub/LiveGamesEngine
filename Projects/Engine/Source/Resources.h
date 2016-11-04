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
		void processPendingItems();

		void load(Resource* resource);
		void unload(Resource* resource);

		void removeResource(u32 id);
		void addResource(Resource* resource);

		const map<u32, Resource*>& getAllResources() const;

		/* shaders */
		Shader* createShader(u32 id, u32 type, const string& file);

		/* programs */
		Program* createProgram(u32 id, const vector<Shader*> shaders);

		/* meshes */
		Mesh* createMesh(u32 id, const string& file);
		Mesh* createMesh(u32 id, u32 primitive, u32 drawType, const Flag& flag);
		Mesh* createMesh(u32 id, const vec2& startPoint, const vec2& size, const vec2& textureSize);

		/*textures */
		Texture* createTexture(u32 id, const string& file, bool generateMipmaps);

		/* materials */
		template <class T> T* createMaterial(u32 id, Program* program, Texture* texture, const vec3& diffuse, const Flag& flag = 0);

		/* template methods */
		template <class T> T* getResource(u32 id) const;

		static u32 getNextAvailableId();
		static Resources& getInstance();

	private:
		map<u32, Resource*> mAllResources;
		vector<ResourceContainer> mPendingItems;
	};

	/* template class methods - begin */
	template <class T>
	T* Resources::createMaterial(u32 id, Program* program, Texture* texture, const vec3& diffuse, const Flag& flag)
	{
		assert(getResource<T>(id) == nullptr);

		T* material = new T(id, diffuse, flag);
		material->setProgram(program);

		if (texture)
		{
			// if we have a texture assign it (don't forget the cast)
			material->setDiffuseTexture(texture);
		}

		addResource(material);

		return static_cast<T*>(material);
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
