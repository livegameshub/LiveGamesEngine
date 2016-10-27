#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include "ResourceContainer.h"

namespace lg
{
	class SpriteMaterial;	
	class Mesh;
	class Material;
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
		
		Resource* getResource(glm::u32 id) const;
		Resource* operator[](glm::u32 id) const;

		const std::map<glm::u32, Resource*>& getAllResources() const;

		/* shaders */
		Shader* createShader(glm::u32 id, glm::u32 type, const std::string& file);

		/* programs */
		Program* createProgram(glm::u32 id, const std::vector<Shader*> shaders);

		/* materials */
		Material* createMaterial(glm::u32 id, Program* program, const glm::vec3& diffuse);
		
		SpriteMaterial* createMaterial(glm::u32 id, Program* program, Texture* texture, const glm::vec3& diffuse);

		DiffuseMaterial* createMaterial(glm::u32 id, Program* program, Texture* texture, const glm::vec3& diffuse, const Flag& flag);
		DiffuseMaterial* createMaterial(glm::u32 id, Program* program, Texture* texture, const glm::vec3& diffuse, const glm::vec3& specular, glm::f32 shininess, const Flag& flag);

		/* meshes */
		Mesh* createMesh(glm::u32 id, const std::string& file);
		Mesh* createMesh(glm::u32 id, glm::u32 primitive, glm::u32 drawType, const Flag& flag);
		Mesh* createMesh(glm::u32 id, const glm::vec2& startPoint, const glm::vec2& size, const glm::vec2& textureSize);

		/*textures */
		Texture* createTexture(glm::u32 id, const std::string& file);

		static glm::u32 getNextAvailableId();
		static Resources& getInstance();

	private:
		std::map<glm::u32, Resource*> mAllResources;
		std::vector<ResourceContainer> mPendingItems;
	};
}

#endif // _RESOURCES_H_
