#include "Node.h"

#include <algorithm>

namespace lg
{
	Node::Node(glm::u32 id)
		: Object(id, IS_ENABLED)
		, mType(NODE)
	{
	}

	Node::Node(glm::u32 id, glm::i32 type)
		: Object(id, IS_ENABLED)
		, mType(type)
	{
	}

	Node::Node(glm::u32 id, glm::i32 type, const Flag& flag)
		: Object(id, flag | IS_ENABLED)
		, mType(type)
	{
	}

	Node::Node(glm::u32 id, const Flag& flag)
		: Object(id, flag | IS_ENABLED)
		, mType(NODE)
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
		assert(getComponent<Component>(component->getType()) == nullptr);

		mComponents.push_back(component);
	}

	void Node::addChild(Node* node)
	{
		assert(node != nullptr);
		/* check if we already have this node in the children */
		assert(getChild<Node>(node->getId()) == nullptr);

		/* set the parent transformation for the child node */
		node->getTransform().setParent(&mTransform);

		mChildren.push_back(node);
	}

	Component* Node::removeComponent(glm::i32 type)
	{
		auto it = std::find_if(mComponents.begin(), mComponents.end(), [type] (Component* component)
		{ 
			return component->getType() == type;
		});

		if (*it)
		{
			mComponents.erase(it);
		}

		return *it;
	}

	Node* Node::removeChild(glm::u32 id)
	{
		auto it = std::find_if(mChildren.begin(), mChildren.end(), [id] (Node* node)
		{
			return node->getId() == id;
		});

		if (*it)
		{
			(*it)->getTransform().setParent(nullptr);

			mChildren.erase(it);
		}

		return *it;
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

	void Node::setType(glm::i32 type)
	{
		mType = type;
	}

	glm::i32 Node::getType() const
	{
		return mType;
	}

	bool Node::isEnabled() const
	{
		return mFlag.isSet(IS_ENABLED);
	}

	bool Node::isVisible() const
	{
		return mFlag.isSet(IS_VISIBLE);
	}
}
