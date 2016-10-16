#include "BasicScene.h"
#include "ModelNode.h"
#include "CameraNode.h"
#include "DirectionalLightNode.h"

namespace ai
{
	BasicScene::BasicScene()
		: mRootNode(0)
		, mAmbientLight(0.1f)
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
		assert(getNode(node->getId()) == nullptr);

		mNodes.insert({ node->getId(), node });	
	}

	void BasicScene::addCamera(CameraNode* camera)
	{
		assert(camera != nullptr);

		mCameras.push_back(camera);
	}

	void BasicScene::addLight(LightNode* light)
	{
		assert(light != nullptr);
		
		mLights.push_back(light);
	}

	void BasicScene::removeCamera(glm::u32 id)
	{
		for (glm::u32 i = 0; i < mCameras.size(); ++i)
		{
			if (mCameras[i]->getId() == id)
			{
				mCameras.erase(mCameras.begin() + i);
			}
		}
	}

	void BasicScene::removeLight(glm::u32 id)
	{
		for (glm::u32 i = 0; i < mLights.size(); ++i)
		{
			if (mLights[i]->getId() == id)
			{
				mLights.erase(mLights.begin() + i);
			}
		}
	}

	BasicNode* BasicScene::removeNode(glm::u32 id)
	{
		auto it = mNodes.find(id);

		/* check if you have the node */
		assert(it != mNodes.end());
		
		mNodes.erase(it);

		if (it->second->getNodeType() == BasicNode::CAMERA_NODE)
		{
			removeCamera(it->second->getId());
		}
		else if (it->second->getNodeType() == BasicNode::LIGHT_NODE)
		{
			removeLight(it->second->getId());
		}

		return it->second;
	}

	BasicNode* BasicScene::operator[](glm::u32 id) const
	{
		return getNode(id);
	}

	BasicNode* BasicScene::getNode(glm::u32 id) const
	{
		auto it = mNodes.find(id);

		if (it == mNodes.end())
		{
			return nullptr;
		}

		return it->second;
	}

	CameraNode* BasicScene::getCameraByIndex(glm::u32 index) const
	{
		assert(index < mCameras.size());

		return mCameras[index];
	}

	LightNode* BasicScene::getLightByIndex(glm::u32 index) const
	{
		assert(index < mLights.size());

		return mLights[index];
	}

	const glm::vec3& BasicScene::getAmbientLight() const
	{
		return mAmbientLight;
	}

	const std::map<glm::u32, BasicNode*>& BasicScene::getNodes() const
	{
		return mNodes;
	}

	const std::vector<CameraNode*>& BasicScene::getCameras() const
	{
		return mCameras;
	}

	const std::vector<LightNode*>& BasicScene::getLights() const
	{
		return mLights;
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

	DirectionalLightNode* BasicScene::createDirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular)
	{
		assert(getNode(id) == nullptr);

		DirectionalLightNode* light = new DirectionalLightNode(id, direction, diffuse, specular);

		addLight(light);
		addNode(light);

		return light;
	}

	void BasicScene::setAmbientLight(const glm::vec3& ambient)
	{
		mAmbientLight = ambient;
	}

	ModelNode* BasicScene::createModel(glm::u32 id, MeshResource* mesh, BasicMaterialResource* material)
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
