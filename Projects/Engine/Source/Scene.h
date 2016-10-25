#ifndef _SCENE_H_
#define _SCENE_H_

#include "Node.h"

namespace lg
{
	class DirectionalLight;
	class Material;
	class Mesh;
	class Model;
	class Camera;
	class Light;

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
		void addLight(Light* light);
		void addCamera(Camera* camera);

		void removeLight(glm::u32 id);
		void removeCamera(glm::u32 id);
		
		Node* removeNode(glm::u32 id);
		Node* operator[](glm::u32 id) const;
		Node* getNode(glm::u32 id) const;

		Camera* getCameraByIndex(glm::u32 index) const;
		Light* getLightByIndex(glm::u32 index) const;

		/* node */
		Node* createNode(glm::u32 id);

		/* model */
		Model* createModel(glm::u32 id, Mesh* mesh, Material* material);

		/* camera */
		Camera* createCamera(glm::u32 id, const glm::vec2& size, const glm::vec3& position);

		/* lights */
		DirectionalLight* createDirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular);

		void setAmbientLight(const glm::vec3& ambient);
		const glm::vec3& getAmbientLight() const;

		const std::map<glm::u32, Node*>& getNodes() const;
		const std::vector<Camera*>& getCameras() const;
		const std::vector<Light*>& getLights() const;

		const Node& getRootNode() const;
		Node& getRootNode();

	protected:
		Node mRootNode;

	private:
		std::map<glm::u32, Node*> mNodes;

		std::vector<Camera*> mCameras;
		std::vector<Light*> mLights;

		glm::vec3 mAmbientLight;
	};
}

#endif // _SCENE_H_
