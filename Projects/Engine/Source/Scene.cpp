#include "Scene.h"
#include "Model.h"
#include "Camera.h"
#include "DirectionalLight.h"

namespace lg
{
	Scene::Scene()
		: mRootNode(0)
		, mAmbientLight(0.1f)
	{
	}

	Scene::Scene(const glm::vec3& ambientLight)
		: mRootNode(0)
		, mAmbientLight(ambientLight)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::init()
	{
	}

	void Scene::update()
	{
		mRootNode.update();
	}

	void Scene::release()
	{
		for (auto it : mNodes)
		{
			Node* node = it.second;

			assert(node != nullptr);
			
			node->release();

			delete node;
			node = nullptr;
		}

		mCameras.clear();
		mNodes.clear();
	}

	void Scene::addNode(Node* node)
	{
		assert(node != nullptr);

		/* check if we already have this node */
		assert(getNode(node->getId()) == nullptr);

		mNodes.insert({ node->getId(), node });	
	}

	void Scene::addCamera(Camera* camera)
	{
		assert(camera != nullptr);

		mCameras.push_back(camera);
	}

	void Scene::addLight(Light* light)
	{
		assert(light != nullptr);
		
		mLights.push_back(light);
	}

	void Scene::removeCamera(glm::u32 id)
	{
		for (glm::u32 i = 0; i < mCameras.size(); ++i)
		{
			if (mCameras[i]->getId() == id)
			{
				mCameras.erase(mCameras.begin() + i);
			}
		}
	}

	void Scene::removeLight(glm::u32 id)
	{
		for (glm::u32 i = 0; i < mLights.size(); ++i)
		{
			if (mLights[i]->getId() == id)
			{
				mLights.erase(mLights.begin() + i);
			}
		}
	}

	Node* Scene::removeNode(glm::u32 id)
	{
		auto it = mNodes.find(id);

		/* check if you have the node */
		assert(it != mNodes.end());
		
		mNodes.erase(it);

		if (it->second->getNodeType() == Node::CAMERA_NODE)
		{
			removeCamera(it->second->getId());
		}
		else if (it->second->getNodeType() == Node::LIGHT_NODE)
		{
			removeLight(it->second->getId());
		}

		return it->second;
	}

	Node* Scene::operator[](glm::u32 id) const
	{
		return getNode(id);
	}

	Node* Scene::getNode(glm::u32 id) const
	{
		auto it = mNodes.find(id);

		if (it == mNodes.end())
		{
			return nullptr;
		}

		return it->second;
	}

	Camera* Scene::getCameraByIndex(glm::u32 index) const
	{
		assert(index < mCameras.size());

		return mCameras[index];
	}

	Light* Scene::getLightByIndex(glm::u32 index) const
	{
		assert(index < mLights.size());

		return mLights[index];
	}

	const glm::vec3& Scene::getAmbientLight() const
	{
		return mAmbientLight;
	}

	const std::map<glm::u32, Node*>& Scene::getNodes() const
	{
		return mNodes;
	}

	const std::vector<Camera*>& Scene::getCameras() const
	{
		return mCameras;
	}

	const std::vector<Light*>& Scene::getLights() const
	{
		return mLights;
	}

	const Node& Scene::getRootNode() const
	{
		return mRootNode;
	}

	Node& Scene::getRootNode()
	{
		return mRootNode;
	}

	Node* Scene::createNode(glm::u32 id)
	{
		assert(getNode(id) == nullptr);

		Node* node = new Node(id);

		addNode(node);

		return node;
	}

	DirectionalLight* Scene::createDirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular)
	{
		assert(getNode(id) == nullptr);

		DirectionalLight* light = new DirectionalLight(id, direction, diffuse, specular);

		addLight(light);
		addNode(light);

		return light;
	}

	void Scene::setAmbientLight(const glm::vec3& ambient)
	{
		mAmbientLight = ambient;
	}

	Model* Scene::createModel(glm::u32 id, Mesh* mesh, Material* material)
	{
		assert(getNode(id) == nullptr);

		Model* model = new Model(id);
		model->setMesh(mesh);
		model->setMaterial(material);

		addNode(model);

		return model;
	}

	Camera* Scene::createCamera(glm::u32 id, const glm::vec2& size, const glm::vec3& position)
	{
		assert(getNode(id) == nullptr);

		Camera* camera = new Camera(id);
		camera->setViewSize(size);
		camera->moveAt(position);

		addCamera(camera);
		addNode(camera);

		return camera;
	}
}
