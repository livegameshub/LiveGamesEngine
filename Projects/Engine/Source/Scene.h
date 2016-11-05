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
		Scene(const vec3& ambientLight);

		virtual ~Scene();		

		virtual void init();
		virtual void update();
		virtual void release();

		/* template methods */
		template <class T> T* getNode(u32 id) const;
		template <class T> T* create(u32 id, i32 type, Node* parent);
		template <class T> T* create(u32 id, i32 type, Node* parent, const vec3& position);
		void remove(u32 id);

		void setAmbientLight(const vec3& ambient);
		const vec3& getAmbientLight() const;

		const map<u32, Node*>& getNodes() const;
		vector<Light*> getLights(i32 type) const;
		vector<Camera*> getCameras() const;

		const Node& getRootNode() const;
		Node& getRootNode();

	protected:
		map<u32, Node*> mNodes;

		vec3 mAmbientLight;
		Node mRootNode;
	};

	template <class T>
	T* Scene::create(u32 id, i32 type, Node* parent)
	{
		assert(getNode<T>(id) == nullptr);

		T* node = new T(id, type);

		if (parent)
		{
			parent->addChild(node);
		}

		mNodes.insert({ node->getId(), node });

		return node;
	}

	template <class T>
	T* Scene::create(u32 id, i32 type, Node* parent, const vec3& position)
	{
		T* node = create<T>(id, type, parent);
		node->getTransform().setPosition(position);

		return node;
	}

	/* template class methods - begin */
	template <class T>
	T* Scene::getNode(u32 id) const
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
