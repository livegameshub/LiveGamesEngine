#include "BasicScene.h"

namespace ai
{
	BasicScene::BasicScene()
		: mRootNode(0)
	{
	}

	BasicScene::~BasicScene()
	{
	}

	void BasicScene::Init()
	{
	}

	void BasicScene::Update()
	{
		mRootNode.Update();
	}

	void BasicScene::Release()
	{
		for (auto it : mNodes)
		{
			BasicNode* node = it.second;

			if (node)
			{
				node->Release();

				delete node;
				node = nullptr;
			}
		}

		mNodes.clear();
	}

	void BasicScene::AddNode(BasicNode* node)
	{
		if (node)
		{
			mNodes.insert({ node->GetId(), node });
		}
	}

	BasicNode* BasicScene::RemoveNode(glm::u32 id)
	{
		auto it = mNodes.find(id);

		if (it != mNodes.end())
		{
			mNodes.erase(it);

			return it->second;
		}

		return nullptr;
	}

	BasicNode* BasicScene::operator[](glm::u32 id) const
	{
		return GetNode(id);
	}

	BasicNode* BasicScene::GetNode(glm::u32 id) const
	{
		auto it = mNodes.find(id);

		if (it != mNodes.end())
		{
			return it->second;
		}

		return nullptr;
	}

	const std::map<glm::u32, BasicNode*>& BasicScene::GetNodes() const
	{
		return mNodes;
	}

	const BasicNode& BasicScene::GetRootNode() const
	{
		return mRootNode;
	}

	BasicNode& BasicScene::GetRootNode()
	{
		return mRootNode;
	}
}
