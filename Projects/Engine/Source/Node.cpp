#include "Node.h"

namespace lg
{
	Node::Node(glm::u32 id)
		: Object(id)
		, mIsEnabled(true)
		, mNodeType(BASIC_NODE)
	{
	}

	Node::Node(glm::u32 id, glm::i32 type)
		: Object(id)
		, mIsEnabled(true)
		, mNodeType(type)
	{
	}

	Node::Node(glm::u32 id, glm::i32 type, const Flag& flag)
		: Object(id, flag)
		, mIsEnabled(true)
		, mNodeType(type)
	{
	}

	Node::Node(glm::u32 id, const Flag& flag)
		: Object(id, flag)
		, mIsEnabled(true)
		, mNodeType(BASIC_NODE)
	{
	}

	Node::~Node()
	{
	}

	void Node::update()
	{
		mTransform.update();
	
		/* update the components */

		for (Component* component : mComponents)
		{
			assert(component != nullptr);

			if (component->isEnabled())
			{
				component->update();
			}
		}

		/* update the children */

		for (Node* child : mChildren)
		{
			assert(child != nullptr);

			if (child->isEnabled())
			{
				child->update();
			}
		}
	}

	void Node::release()
	{
		/* release the components */

		for (Component* component : mComponents)
		{
			assert(component != nullptr);
			
			SAFE_DELETE(component);
		}
	}

	void Node::addComponent(Component* component)
	{
		assert(component != nullptr);
		/* check if we already have this type of component */
		assert(getComponent(component->getComponentType()) == nullptr);

		mComponents.push_back(component);
	}

	void Node::addChild(Node* node)
	{
		assert(node != nullptr);

		/* set the parent transformation for the child node */
		node->getTransform().setParentTransform(&mTransform);

		mChildren.push_back(node);
	}

	Component* Node::getComponent(glm::i32 type) const
	{
		/* if we do not find any component we should return nullptr */

		for (Component* component : mComponents)
		{
			if (component->getComponentType() == type)
			{
				return component;
			}
		}

		return nullptr;
	}

	Component* Node::operator[](glm::i32 type) const
	{
		return getComponent(type);
	}

	Component* Node::removeComponent(glm::i32 type)
	{
		for (glm::u32 i = 0; i < mComponents.size(); ++i)
		{
			Component* component = mComponents[i];

			if (component->getComponentType() == type)
			{
				mComponents.erase(mComponents.begin() + i);

				return component;
			}
		}

		return nullptr;
	}

	Node* Node::getChild(glm::u32 id) const
	{
		/* if we do not find any node we should return nullptr */

		for (Node* node : mChildren)
		{
			if (node->getId() == id)
			{
				return node;
			}
		}

		return nullptr;
	}

	Node* Node::operator[](glm::u32 id) const
	{
		return getChild(id);
	}

	Node* Node::removeChild(glm::u32 id)
	{
		for (glm::u32 i = 0; i < mChildren.size(); ++i)
		{
			Node* node = mChildren[i];

			if (node->getId() == id)
			{
				mChildren.erase(mChildren.begin() + i);

				/* remove the parent transformation */
				node->getTransform().setParentTransform(nullptr);

				return node;
			}
		}

		return nullptr;
	}

	const std::vector<Component*>& Node::getComponents() const
	{
		return mComponents;
	}

	const std::vector<Node*>& Node::getChildren() const
	{
		return mChildren;
	}

	const Transform& Node::getTransform() const
	{
		return mTransform;
	}

	Transform& Node::getTransform()
	{
		return mTransform;
	}

	void Node::setNodeType(glm::i32 type)
	{
		mNodeType = type;
	}

	glm::i32 Node::getNodeType() const
	{
		return mNodeType;
	}

	void Node::setEnabled(bool value)
	{
		mIsEnabled = value;
	}

	bool Node::isEnabled() const
	{
		return mIsEnabled;
	}
}
