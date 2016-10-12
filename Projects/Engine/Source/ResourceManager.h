#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include "Flag.h"

namespace ai
{
	class MeshResource;
	class MaterialResource;
	class ProgramResource;
	class BasicResource;
	class ShaderResource;

	class ENGINE_API ResourceManager
	{
	public:
		void release();
		void flushPendingItems();

		void removeResource(glm::u32 id);
		void addResource(BasicResource* resource);
		void addPendingItem(BasicResource* resource, bool isUnloaded);
		
		BasicResource* getResource(glm::u32 id) const;
		BasicResource* operator[](glm::u32 id) const;

		const std::map<glm::u32, BasicResource*>& getAllResources() const;

		/* shaders */
		ShaderResource* createShader(glm::u32 id, glm::u32 type, const std::string& file);

		/* programs */
		ProgramResource* createProgram(glm::u32 id, const std::vector<ShaderResource*> shaders);

		/* materials */
		MaterialResource* createMaterial(glm::u32 id, ProgramResource* program, const glm::vec3& diffuse, const Flag& flag = 0);

		/* meshes */
		MeshResource* createMesh(glm::u32 id, const std::string& file);

		static ResourceManager& getInstance();

	private:
		std::map<glm::u32, BasicResource*> mAllResources;
		std::vector<BasicResource*> mPendingItems;
	};
}

#endif // _RESOURCE_MANAGER_H_
