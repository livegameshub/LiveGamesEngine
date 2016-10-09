#include "BasicScene.h"
#include "ModelNode.h"
#include "CameraNode.h"

namespace ai
{
	BasicScene::BasicScene()
		: mRootNode(0)
	{
	}

	BasicScene::~BasicScene()
	{
	}

	void BasicScene::init()
	{
	}

	void BasicScene::update()
	{
		mRootNode.update();
	}

	void BasicScene::release()
	{
		for (auto it : mNodes)
		{
			BasicNode* node = it.second;

			assert(node != nullptr);
			
			node->release();

			delete node;
			node = nullptr;
		}

		mCameras.clear();
		mNodes.clear();
	}

	void BasicScene::addNode(BasicNode* node)
	{
		assert(node != nullptr);
		/* check if we already have this node */
		assert(getNode(node->GetId()) == nullptr);

		mNodes.insert({ node->GetId(), node });	
	}

	void BasicScene::addCamera(CameraNode* camera)
	{
		assert(camera != nullptr);

		mCameras.push_back(camera);
	}

	BasicNode* BasicScene::removeNode(glm::u32 id)
	{
		auto it = mNodes.find(id);

		/* check if you have the node */
		assert(it != mNodes.end());
		
		mNodes.erase(it);

		return it->second;
	}

	BasicNode* BasicScene::operator[](glm::u32 id) const
	{
		return getNode(id);
	}

	BasicNode* BasicScene::getNode(glm::u32 id) const
	{
		auto it = mNodes.find(id);

		#ifdef _DEBUG
		if (it == mNodes.end())
		{
			return nullptr;
		}
		#endif

		return it->second;
	}

	CameraNode* BasicScene::getCameraByIndex(glm::u32 index) const
	{
		assert(index < mCameras.size());

		return mCameras[index];
	}

	const std::map<glm::u32, BasicNode*>& BasicScene::getNodes() const
	{
		return mNodes;
	}

	const BasicNode& BasicScene::getRootNode() const
	{
		return mRootNode;
	}

	BasicNode& BasicScene::getRootNode()
	{
		return mRootNode;
	}

	BasicNode* BasicScene::createNode(glm::u32 id)
	{
		assert(getNode(id) == nullptr);

		BasicNode* node = new BasicNode(id);

		addNode(node);

		return node;
	}

	ModelNode* BasicScene::createModel(glm::u32 id, MeshResource* mesh, MaterialResource* material)
	{
		assert(getNode(id) == nullptr);

		ModelNode* model = new ModelNode(id);
		model->setMesh(mesh);
		model->setMaterial(material);

		addNode(model);

		return model;
	}

	CameraNode* BasicScene::createCamera(glm::u32 id, const glm::vec2& size, const glm::vec3& position)
	{
		assert(getNode(id) == nullptr);

		CameraNode* camera = new CameraNode(id);
		camera->setViewSize(size);
		camera->moveAt(position);

		addCamera(camera);
		addNode(camera);

		return camera;
	}
}
