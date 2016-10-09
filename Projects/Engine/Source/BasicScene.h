#ifndef _BASIC_SCENE_H_
#define _BASIC_SCENE_H_

#include "BasicNode.h"

namespace ai
{
	class MaterialResource;
	class MeshResource;
	class ModelNode;
	class CameraNode;

	class ENGINE_API BasicScene
	{
	public:
		BasicScene();

		virtual ~BasicScene();

		virtual void init();
		virtual void update();
		virtual void release();
		
		void addNode(BasicNode* node);
		void addCamera(CameraNode* camera);

		void removeCamera(glm::u32 id);
		
		BasicNode* removeNode(glm::u32 id);
		BasicNode* operator[](glm::u32 id) const;
		BasicNode* getNode(glm::u32 id) const;

		CameraNode* getCameraByIndex(glm::u32 index) const;

		/* node */
		BasicNode* createNode(glm::u32 id);

		/* model */
		ModelNode* createModel(glm::u32 id, MeshResource* mesh, MaterialResource* material);

		/* camera */
		CameraNode* createCamera(glm::u32 id, const glm::vec2& size, const glm::vec3& position);

		const std::map<glm::u32, BasicNode*>& getNodes() const;
		const std::vector<CameraNode*>& getCameras() const;

		const BasicNode& getRootNode() const;
		BasicNode& getRootNode();

	protected:
		BasicNode mRootNode;

	private:
		std::map<glm::u32, BasicNode*> mNodes;
		std::vector<CameraNode*> mCameras;
	};
}

#endif
