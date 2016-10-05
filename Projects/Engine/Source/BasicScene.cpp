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

			assert(node != nullptr);
			
			node->Release();

			delete node;
			node = nullptr;
		}

		mNodes.clear();
	}

	void BasicScene::AddNode(BasicNode* node)
	{
		assert(node != nullptr);
		
		mNodes.insert({ node->GetId(), node });	
	}

	BasicNode* BasicScene::RemoveNode(glm::u32 id)
	{
		auto it = mNodes.find(id);

		/* check if you have the node */
		assert(it != mNodes.end());
		
		mNodes.erase(it);

		return it->second;
	}

	BasicNode* BasicScene::operator[](glm::u32 id) const
	{
		return GetNode(id);
	}

	BasicNode* BasicScene::GetNode(glm::u32 id) const
	{
		auto it = mNodes.find(id);

		assert(it != mNodes.end());
		
		return it->second;
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
