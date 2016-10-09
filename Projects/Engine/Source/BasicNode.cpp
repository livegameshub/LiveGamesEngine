#include "BasicNode.h"

namespace ai
{
	BasicNode::BasicNode(glm::u32 id)
		: BasicElement(id)
		, mIsEnabled(true)
		, mNodeType(BASIC_NODE)
	{
	}

	BasicNode::BasicNode(glm::u32 id, glm::i32 type)
		: BasicElement(id)
		, mIsEnabled(true)
		, mNodeType(type)
	{
	}

	BasicNode::BasicNode(glm::u32 id, glm::i32 type, const Flag& flag)
		: BasicElement(id, flag)
		, mIsEnabled(true)
		, mNodeType(type)
	{
	}

	BasicNode::BasicNode(glm::u32 id, const Flag& flag)
		: BasicElement(id, flag)
		, mIsEnabled(true)
		, mNodeType(BASIC_NODE)
	{
	}

	BasicNode::~BasicNode()
	{
	}

	void BasicNode::update()
	{
		mTransform.update();
	
		/* update the components */

		for (BasicComponent* component : mComponents)
		{
			assert(component != nullptr);

			if (component->IsEnabled())
			{
				component->update();
			}
		}

		/* update the children */

		for (BasicNode* child : mChildren)
		{
			assert(child != nullptr);

			if (child->isEnabled())
			{
				child->update();
			}
		}
	}

	void BasicNode::release()
	{
		/* release the components */

		for (BasicComponent* component : mComponents)
		{
			assert(component != nullptr);
			
			delete component;
			component = nullptr;
		}
	}

	void BasicNode::addComponent(BasicComponent* component)
	{
		assert(component != nullptr);
		/* check if we already have this type of component */
		assert(getComponent(component->GetComponentType()) == nullptr);

		mComponents.push_back(component);
	}

	void BasicNode::addChild(BasicNode* node)
	{
		assert(node != nullptr);

		/* set the parent transformation for the child node */
		node->getTransform().SetParentTransform(&mTransform);

		mChildren.push_back(node);
	}

	BasicComponent* BasicNode::getComponent(glm::i32 type) const
	{
		/* if we do not find any component we should return nullptr */

		for (BasicComponent* component : mComponents)
		{
			if (component->GetComponentType() == type)
			{
				return component;
			}
		}

		return nullptr;
	}

	BasicComponent* BasicNode::operator[](glm::i32 type) const
	{
		return getComponent(type);
	}

	BasicComponent* BasicNode::removeComponent(glm::i32 type)
	{
		for (glm::u32 i = 0; i < mComponents.size(); ++i)
		{
			BasicComponent* component = mComponents[i];

			if (component->GetComponentType() == type)
			{
				mComponents.erase(mComponents.begin() + i);

				return component;
			}
		}

		return nullptr;
	}

	BasicNode* BasicNode::getChild(glm::u32 id) const
	{
		/* if we do not find any node we should return nullptr */

		for (BasicNode* node : mChildren)
		{
			if (node->GetId() == id)
			{
				return node;
			}
		}

		return nullptr;
	}

	BasicNode* BasicNode::operator[](glm::u32 id) const
	{
		return getChild(id);
	}

	BasicNode* BasicNode::removeChild(glm::u32 id)
	{
		for (glm::u32 i = 0; i < mChildren.size(); ++i)
		{
			BasicNode* node = mChildren[i];

			if (node->GetId() == id)
			{
				mChildren.erase(mChildren.begin() + i);

				/* remove the parent transformation */
				node->getTransform().SetParentTransform(nullptr);

				return node;
			}
		}

		return nullptr;
	}

	const std::vector<BasicComponent*>& BasicNode::getComponents() const
	{
		return mComponents;
	}

	const std::vector<BasicNode*>& BasicNode::getChildren() const
	{
		return mChildren;
	}

	const TransformComponent& BasicNode::getTransform() const
	{
		return mTransform;
	}

	TransformComponent& BasicNode::getTransform()
	{
		return mTransform;
	}

	void BasicNode::setNodeType(glm::i32 type)
	{
		mNodeType = type;
	}

	glm::i32 BasicNode::getNodeType() const
	{
		return mNodeType;
	}

	void BasicNode::setEnabled(bool value)
	{
		mIsEnabled = value;
	}

	bool BasicNode::isEnabled() const
	{
		return mIsEnabled;
	}
}
