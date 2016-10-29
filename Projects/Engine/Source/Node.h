#ifndef _NODE_H_
#define _NODE_H_

#include "Object.h"
#include "Transform.h"

namespace lg
{
	class Transform;

	class ENGINE_API Node : public Object
	{
	public:
		enum NodeFlag : glm::i32
		{
			IS_ENABLED = 1,
			IS_VISIBLE = 2
		};

		enum NodeType : glm::i32
		{
			NODE,
			CAMERA,
			MESH_RENDERER,
			SPRITE,
			LIGHT
		};

		Node(glm::u32 id);
		Node(glm::u32 id, glm::i32 type);
		Node(glm::u32 id, glm::i32 type, const Flag& flag);
		Node(glm::u32 id, const Flag& flag);

		virtual ~Node();

		virtual void update();
		virtual void release();
		
		/* nodes */
		void addChild(Node* node);
		Node* removeChild(glm::u32 id);

		/* components */
		void addComponent(Component* component);
		Component* removeComponent(glm::i32 type);

		/* template functions */
		template <class T> T* getChild(glm::u32 id) const;
		template <class T> T* getFistChild(glm::u32 type) const;
		template <class T> T* getComponent(glm::i32 type) const;
		
		const std::vector<Component*>& getComponents() const;
		const std::vector<Node*>& getChildren() const;
		const Transform& getTransform() const;
		Transform& getTransform();

		void setType(glm::i32 type);
		glm::i32 getType() const;

		bool isVisible() const;
		bool isEnabled() const;

	protected:
		Transform mTransform;

	private:
		std::vector<Component*> mComponents;
		std::vector<Node*> mChildren;

		glm::i32 mType;
	};

	/* template class methods - begin */
	template <class T>
	T* Node::getChild(glm::u32 id) const
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
	T* Node::getComponent(glm::i32 type) const
	{
		/* if we do not find any component we should return nullptr */

		for (Component* component : mComponents)
		{
			if (component->getType() == type)
			{
				return static_cast<T*>(component);
			}
		}

		return nullptr;
	}

	template <class T>
	T* Node::getFistChild(glm::u32 type) const
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
