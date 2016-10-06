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
		mTransform.Update();
	
		/* update the components */

		for (BasicComponent* component : mComponents)
		{
			assert(component != nullptr);

			if (component->IsEnabled())
			{
				component->Update();
			}
		}

		/* update the children */

		for (BasicNode* child : mChildren)
		{
			assert(child != nullptr);

			if (child->IsEnabled())
			{
				child->update();
			}
		}
	}

	void BasicNode::Release()
	{
		/* release the components */

		for (BasicComponent* component : mComponents)
		{
			assert(component != nullptr);
			
			delete component;
			component = nullptr;
		}
	}

	void BasicNode::AddComponent(BasicComponent* component)
	{
		assert(component != nullptr);
		
		/* check if we already have this type of component */

		if (!GetComponent(component->GetComponentType()))
		{
			mComponents.push_back(component);
		}
	}

	void BasicNode::AddChild(BasicNode* node)
	{
		assert(node != nullptr);

		/* set the parent transformation for the child node */

		node->GetTransform().SetParentTransform(&mTransform);

		mChildren.push_back(node);
	}

	BasicComponent* BasicNode::GetComponent(glm::i32 type) const
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
		return GetComponent(type);
	}

	BasicComponent* BasicNode::RemoveComponent(glm::i32 type)
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

	BasicNode* BasicNode::GetChild(glm::u32 id) const
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
		return GetChild(id);
	}

	BasicNode* BasicNode::RemoveChild(glm::u32 id)
	{
		for (glm::u32 i = 0; i < mChildren.size(); ++i)
		{
			BasicNode* node = mChildren[i];

			if (node->GetId() == id)
			{
				mChildren.erase(mChildren.begin() + i);

				/* remove the parent transformation */
				node->GetTransform().SetParentTransform(nullptr);

				return node;
			}
		}

		return nullptr;
	}

	const std::vector<BasicComponent*>& BasicNode::GetComponents() const
	{
		return mComponents;
	}

	const std::vector<BasicNode*>& BasicNode::GetChildren() const
	{
		return mChildren;
	}

	const TransformComponent& BasicNode::GetTransform() const
	{
		return mTransform;
	}

	TransformComponent& BasicNode::GetTransform()
	{
		return mTransform;
	}

	void BasicNode::SetNodeType(glm::i32 type)
	{
		mNodeType = type;
	}

	glm::i32 BasicNode::GetNodeType() const
	{
		return mNodeType;
	}

	void BasicNode::SetEnabled(bool value)
	{
		mIsEnabled = value;
	}

	bool BasicNode::IsEnabled() const
	{
		return mIsEnabled;
	}
}
