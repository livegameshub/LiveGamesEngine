#include "Node.h"

#include <algorithm>

namespace lg
{
	Node::Node(u32 id, i32 type)
		: Object(id)
		, mRenderer(nullptr)
		, mParent(nullptr)
		, mIsEnabled(true)
		, mType(type)
	{
	}

	Node::~Node()
	{
	}

	void Node::addChild(Node* node)
	{
		assert(node != nullptr);
		assert(getChild<Node>(node->getId()) == nullptr);

		node->setParent(this);
		node->getTransform().setParent(&getTransform());

		mChildren.push_back(node);
	}

	Node* Node::removeChild(u32 id)
	{
		auto it = find_if(mChildren.begin(), mChildren.end(), [id](Node* node)
		{
			return node->getId() == id;
		});

		if (*it)
		{
			(*it)->setParent(nullptr);
			(*it)->getTransform().setParent(nullptr);

			mChildren.erase(it);
		}

		return *it;
	}

	void Node::update()
	{
		mTransform.update();

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
		if (mRenderer)
		{
			mRenderer->release();
		}
	}

	void Node::setRenderer(MeshRenderer* renderer)
	{
		mRenderer = renderer;
	}

	void Node::setParent(Node* parent)
	{
		mParent = parent;
	}

	Node* Node::getParent() const
	{
		return mParent;
	}

	MeshRenderer* Node::getRenderer() const
	{
		return mRenderer;
	}

	Transform& Node::getTransform()
	{
		return mTransform;
	}

	const Transform& Node::getTransform() const
	{
		return mTransform;
	}

	const vector<Node*>& Node::getChildren() const
	{
		return mChildren;
	}

	void Node::setType(i32 type)
	{
		mType = type;
	}

	i32 Node::getType() const
	{
		return mType;
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
