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
	}

	void BasicNode::AddChild(BasicNode* node)
	{
	}

	BasicComponent* BasicNode::GetComponent(i32 type) const
	{
	}

	BasicComponent* BasicNode::operator[](i32 type) const
	{
	}

	BasicComponent* BasicNode::RemoveComponent(i32 type)
	{
	}

	BasicNode* BasicNode::GetChild(u32 id) const
	{
	}

	BasicNode* BasicNode::operator[](u32 id) const
	{
	}

	BasicNode* BasicNode::RemoveChild(u32 id)
	{
	}

	const std::vector<BasicComponent*>& BasicNode::GetComponents() const
	{
		return mComponents;
	}

	const std::vector<BasicNode*>& BasicNode::GetChildren() const
	{
		return mChildren;
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
