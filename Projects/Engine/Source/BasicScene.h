#ifndef _BASIC_SCENE_H_
#define _BASIC_SCENE_H_

#include "BasicNode.h"

namespace ai
{
	class DirectionalLightNode;
	class BasicMaterial;
	class MeshResource;
	class ModelNode;
	class CameraNode;
	class LightNode;

	class ENGINE_API BasicScene
	{
	public:
		BasicScene();
		BasicScene(const glm::vec3& ambientLight);

		virtual ~BasicScene();

		virtual void init();
		virtual void update();
		virtual void release();
		
		void addNode(BasicNode* node);
		void addLight(LightNode* light);
		void addCamera(CameraNode* camera);

		void removeLight(glm::u32 id);
		void removeCamera(glm::u32 id);
		
		BasicNode* removeNode(glm::u32 id);
		BasicNode* operator[](glm::u32 id) const;
		BasicNode* getNode(glm::u32 id) const;

		CameraNode* getCameraByIndex(glm::u32 index) const;
		LightNode* getLightByIndex(glm::u32 index) const;

		/* node */
		BasicNode* createNode(glm::u32 id);

		/* model */
		ModelNode* createModel(glm::u32 id, MeshResource* mesh, BasicMaterial* material);

		/* camera */
		CameraNode* createCamera(glm::u32 id, const glm::vec2& size, const glm::vec3& position);

		/* lights */
		DirectionalLightNode* createDirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular);

		void setAmbientLight(const glm::vec3& ambient);
		const glm::vec3& getAmbientLight() const;

		const std::map<glm::u32, BasicNode*>& getNodes() const;
		const std::vector<CameraNode*>& getCameras() const;
		const std::vector<LightNode*>& getLights() const;

		const BasicNode& getRootNode() const;
		BasicNode& getRootNode();

	protected:
		BasicNode mRootNode;

	private:
		std::map<glm::u32, BasicNode*> mNodes;

		std::vector<CameraNode*> mCameras;
		std::vector<LightNode*> mLights;

		glm::vec3 mAmbientLight;
	};
}

#endif // _BASIC_SCENE_H_
