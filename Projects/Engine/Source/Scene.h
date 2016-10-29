#ifndef _SCENE_H_
#define _SCENE_H_

#include "Node.h"

namespace lg
{
	class DirectionalLight;
	class Material;
	class Mesh;
	class MeshRenderer;
	class Camera;
	class Light;
	class Sprite;

	class ENGINE_API Scene
	{
	public:
		Scene();
		Scene(const glm::vec3& ambientLight);

		virtual ~Scene();

		virtual void init();
		virtual void update();
		virtual void release();
		
		void addNode(Node* node);
		Node* removeNode(glm::u32 id);

		/* node */
		Node* createNode(glm::u32 id);

		/* mesh rendere */
		MeshRenderer* createRenderable(glm::u32 id, Mesh* mesh, Material* material);

		/* sprite */
		Sprite* createSprite(glm::u32 id, Mesh* mesh, Material* material, const glm::vec2& size);

		/* camera */
		Camera* createCamera(glm::u32 id, const glm::vec2& size, const glm::vec3& position);

		/* lights */
		DirectionalLight* createDirectionalLight(glm::u32 id, const glm::vec3& direction);
		DirectionalLight* createDirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular);

		/* template methods */
		template <class T> T* getNode(glm::u32 id) const;

		void setAmbientLight(const glm::vec3& ambient);
		const glm::vec3& getAmbientLight() const;

		const std::map<glm::u32, Node*>& getNodes() const;
		std::vector<Camera*> getCameras() const;
		std::vector<Light*> getLights() const;

		const Node& getRootNode() const;
		Node& getRootNode();

	protected:
		Node mRootNode;

	private:
		std::map<glm::u32, Node*> mNodes;

		glm::vec3 mAmbientLight;
	};

	/* template class methods - begin */
	template <class T>
	T* Scene::getNode(glm::u32 id) const
	{
		auto it = mNodes.find(id);

		if (it == mNodes.end())
		{
			return nullptr;
		}

		return static_cast<T*>(it->second);
	}
	/* template class methods - end */
}

#endif // _SCENE_H_
