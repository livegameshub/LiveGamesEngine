#include "Scene.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Resources.h"
#include "Sprite.h"

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

			SAFE_DELETE(node);
		}

		mNodes.clear();
	}

	void Scene::addNode(Node* node)
	{
		assert(node != nullptr);

		/* check if we already have this node */
		assert(getNode<Node>(node->getId()) == nullptr);

		mNodes.insert({ node->getId(), node });	
	}


	Node* Scene::removeNode(glm::u32 id)
	{
		auto it = mNodes.find(id);

		/* check if you have the node */
		assert(it != mNodes.end());
		
		mNodes.erase(it);

		return it->second;
	}

	const glm::vec3& Scene::getAmbientLight() const
	{
		return mAmbientLight;
	}

	const std::map<glm::u32, Node*>& Scene::getNodes() const
	{
		return mNodes;
	}

	std::vector<Camera*> Scene::getCameras() const
	{
		std::vector<Camera*> cameras;

		for (auto pair : mNodes)
		{
			if (pair.second->getType() == Node::CAMERA)
			{
				cameras.push_back(static_cast<Camera*>(pair.second));
			}
		}

		return cameras;
	}

	std::vector<Light*> Scene::getLights() const
	{
		std::vector<Light*> lights;

		for (auto pair : mNodes)
		{
			if (pair.second->getType() == Node::LIGHT)
			{
				lights.push_back(static_cast<Light*>(pair.second));
			}
		}

		return lights;
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
		assert(getNode<Node>(id) == nullptr);

		Node* node = new Node(id);

		addNode(node);

		return node;
	}

	DirectionalLight* Scene::createDirectionalLight(glm::u32 id, const glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular)
	{
		assert(getNode<DirectionalLight>(id) == nullptr);

		DirectionalLight* light = new DirectionalLight(id, direction, diffuse, specular);

		addNode(light);

		return light;
	}

	MeshRenderer* Scene::createRenderable(glm::u32 id, Mesh* mesh, Material* material)
	{
		assert(getNode<MeshRenderer>(id) == nullptr);

		MeshRenderer* model = new MeshRenderer(id);
		model->setMaterial(material);
		model->setMesh(mesh);

		addNode(model);

		return model;
	}

	Sprite* Scene::createSprite(glm::u32 id, Mesh* mesh, Material* material, const glm::vec2& size)
	{
		assert(getNode<Sprite>(id) == nullptr);

		Sprite* sprite = new Sprite(id, size);
		sprite->setMaterial(material);
		sprite->setMesh(mesh);

		addNode(sprite);

		return sprite;
	}

	Camera* Scene::createCamera(glm::u32 id, const glm::vec2& size, const glm::vec3& position)
	{
		assert(getNode<Camera>(id) == nullptr);

		Camera* camera = new Camera(id);
		camera->setViewSize(size);
		camera->moveAt(position);

		addNode(camera);

		return camera;
	}

	DirectionalLight* Scene::createDirectionalLight(glm::u32 id, const glm::vec3& direction)
	{
		assert(getNode<DirectionalLight>(id) == nullptr);

		DirectionalLight* light = new DirectionalLight(id, direction);

		addNode(light);

		return light;
	}

	void Scene::setAmbientLight(const glm::vec3& ambient)
	{
		mAmbientLight = ambient;
	}
}
