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

		void removeResource(glm::u32 id);
		void addResource(Resource* resource);

		const std::map<glm::u32, Resource*>& getAllResources() const;

		/* shaders */
		Shader* createShader(glm::u32 id, glm::u32 type, const std::string& file);

		/* programs */
		Program* createProgram(glm::u32 id, const std::vector<Shader*> shaders);

		/* meshes */
		Mesh* createMesh(glm::u32 id, const std::string& file);
		Mesh* createMesh(glm::u32 id, glm::u32 primitive, glm::u32 drawType, const Flag& flag);
		Mesh* createMesh(glm::u32 id, const glm::vec2& startPoint, const glm::vec2& size, const glm::vec2& textureSize);

		/*textures */
		Texture* createTexture(glm::u32 id, const std::string& file, bool generateMipmaps);

		/* materials */
		template <class T> T* createMaterial(glm::u32 id, Program* program, Texture* texture, const glm::vec3& diffuse, const Flag& flag = 0);

		template <class T> T* getResource(glm::u32 id) const;
		template <class T> T* operator[](glm::u32 id) const;

		static glm::u32 getNextAvailableId();
		static Resources& getInstance();

	private:
		std::map<glm::u32, Resource*> mAllResources;
		std::vector<ResourceContainer> mPendingItems;
	};

	/* template class methods - begin */
	template <class T>
	T* Resources::createMaterial(glm::u32 id, Program* program, Texture* texture, const glm::vec3& diffuse, const Flag& flag)
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
	T* Resources::getResource(glm::u32 id) const
	{
		auto it = mAllResources.find(id);

		if (it == mAllResources.end())
		{
			return nullptr;
		}

		return static_cast<T*>(it->second);
	}

	template <class T>
	T* Resources::operator[](glm::u32 id) const
	{
		return getResource<T>(id);
	}
	/* template class methods - end */
}

#endif // _RESOURCES_H_
