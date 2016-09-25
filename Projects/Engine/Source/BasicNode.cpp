#include "BasicNode.h"

namespace ai
{
	BasicNode::BasicNode(u32 id)
		: BasicElement(id)
		, mIsEnabled(true)
		, mNodeType(BASIC_NODE)
	{
	}

	BasicNode::BasicNode(u32 id, i32 type)
		: BasicElement(id)
		, mIsEnabled(true)
		, mNodeType(type)
	{
	}

	BasicNode::BasicNode(u32 id, i32 type, const Flag& flag)
		: BasicElement(id, flag)
		, mIsEnabled(true)
		, mNodeType(type)
	{
	}

	BasicNode::BasicNode(u32 id, const Flag& flag)
		: BasicElement(id, flag)
		, mIsEnabled(true)
		, mNodeType(BASIC_NODE)
	{
	}

	BasicNode::~BasicNode()
	{
	}

	void BasicNode::Update()
	{
		mTransform.Update();
	
		/* update the components */

		for (BasicComponent* component : mComponents)
		{
			if (component && component->IsEnabled())
			{
				component->Update();
			}
		}

		/* update the children */

		for (BasicNode* child : mChildren)
		{
			if (child && child->IsEnabled())
			{
				child->Update();
			}
		}
	}

	void BasicNode::Release()
	{
		/* release the components */

		for (BasicComponent* component : mComponents)
		{
			if (component)
			{
				delete component;
				component = nullptr;
			}
		}
	}

	void BasicNode::AddComponent(BasicComponent* component)
	{
		if (component)
		{
			/* check if we already have this type of component */

			if (!GetComponent(component->GetComponentType()))
			{
				mComponents.push_back(component);
			}
		}
	}

	void BasicNode::AddChild(BasicNode* node)
	{
		if (node)
		{
			/* set the parent transformation for the child node */

			node->GetTransform().SetParentTransform(&mTransform);

			mChildren.push_back(node);
		}
	}

	BasicComponent* BasicNode::GetComponent(i32 type) const
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

	BasicComponent* BasicNode::operator[](i32 type) const
	{
		return GetComponent(type);
	}

	BasicComponent* BasicNode::RemoveComponent(i32 type)
	{
		for (u32 i = 0; i < mComponents.size(); ++i)
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

	BasicNode* BasicNode::GetChild(u32 id) const
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

	BasicNode* BasicNode::operator[](u32 id) const
	{
		return GetChild(id);
	}

	BasicNode* BasicNode::RemoveChild(u32 id)
	{
		for (u32 i = 0; i < mChildren.size(); ++i)
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

	const Transform& BasicNode::GetTransform() const
	{
		return mTransform;
	}

	Transform& BasicNode::GetTransform()
	{
		return mTransform;
	}

	void BasicNode::SetNodeType(i32 type)
	{
		mNodeType = type;
	}

	i32 BasicNode::GetNodeType() const
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
