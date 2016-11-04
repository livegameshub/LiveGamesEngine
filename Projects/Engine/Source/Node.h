#ifndef _NODE_H_
#define _NODE_H_

#include "Object.h"
#include "Transform.h"
#include "MeshRenderer.h"

namespace lg
{
	class Transform;

	class ENGINE_API Node : public Object
	{
	public:
		enum NodeType : i32
		{
			NODE,
			CAMERA,
			MODEL,
			SPOT_LIGHT,
			POINT_LIGHT,
			DIRECTIONAL_LIGHT
		};

		Node(u32 id, i32 type);

		virtual ~Node();

		virtual void update();
		virtual void release();

		void addChild(Node* node);
		Node* removeChild(u32 id);

		/* template functions */
		template <class T> T* getChild(u32 id) const;
		template <class T> T* getFistChild(u32 type) const;

		const vector<Node*>& getChildren() const;

		const Transform& getTransform() const;
		Transform& getTransform();

		void setRenderer(MeshRenderer* renderer);
		void setParent(Node* parent);
		void setType(i32 type);

		MeshRenderer* getRenderer() const;
		Node* getParent() const;
		i32 getType() const;

		void setEnabled(bool value);
		bool isEnabled() const;

	protected:
		vector<Node*> mChildren;

		Transform mTransform;
		MeshRenderer* mRenderer;
		Node* mParent;

		bool mIsEnabled;
		i32 mType;
	};

	/* template class methods - begin */
	template <class T>
	T* Node::getChild(u32 id) const
	{
		/* if we do not find any node we should return nullptr */

		for (Node* node : mChildren)
		{
			if (node->getId() == id)
			{
				return static_cast<T*>(node);
			}
		}

		return nullptr;
	}

	template <class T>
	T* Node::getFistChild(u32 type) const
	{
		for (Node* node : mChildren)
		{
			if (node->getType() == type)
			{
				return static_cast<T*>(node);
			}
		}

		return nullptr;
	}
	/* template class methods - end */
}

#endif // _NODE_H_
