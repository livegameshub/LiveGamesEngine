#include "Scene.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Resources.h"
#include "Sprite.h"

namespace lg
{
	Scene::Scene()
		: mAmbientLight(0.1f)
		, mRootNode(0, Node::NODE)
		
	{
	}

	Scene::Scene(const vec3& ambientLight)
		: mAmbientLight(ambientLight)
		, mRootNode(0, Node::NODE)
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
			assert(it.second != nullptr);

			it.second->release();

			SAFE_DELETE(it.second);
		}

		mNodes.clear();
	}

	Node* Scene::removeNode(u32 id)
	{
		auto it = mNodes.find(id);

		assert(it != mNodes.end());
		mNodes.erase(it);

		return it->second;
	}

	const vec3& Scene::getAmbientLight() const
	{
		return mAmbientLight;
	}

	const map<u32, Node*>& Scene::getNodes() const
	{
		return mNodes;
	}

	vector<Camera*> Scene::getCameras() const
	{
		vector<Camera*> cameras;

		for (auto pair : mNodes)
		{
			if (pair.second->getType() == Node::CAMERA)
			{
				cameras.push_back(static_cast<Camera*>(pair.second));
			}
		}

		return cameras;
	}

	vector<Light*> Scene::getLights(i32 type) const
	{
		vector<Light*> lights;

		for (auto pair : mNodes)
		{
			if (pair.second->getType() == type)
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

	void Scene::setAmbientLight(const vec3& ambient)
	{
		mAmbientLight = ambient;
	}
}
