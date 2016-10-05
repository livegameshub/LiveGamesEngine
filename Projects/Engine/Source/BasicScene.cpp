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

	void BasicScene::init()
	{
	}

	void BasicScene::update()
	{
		mRootNode.update();
	}

	void BasicScene::release()
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

	void BasicScene::addNode(BasicNode* node)
	{
		assert(node != nullptr);
		
		mNodes.insert({ node->GetId(), node });	
	}

	BasicNode* BasicScene::removeNode(glm::u32 id)
	{
		auto it = mNodes.find(id);

		/* check if you have the node */
		assert(it != mNodes.end());
		
		mNodes.erase(it);

		return it->second;
	}

	BasicNode* BasicScene::operator[](glm::u32 id) const
	{
		return getNode(id);
	}

	BasicNode* BasicScene::getNode(glm::u32 id) const
	{
		auto it = mNodes.find(id);

		assert(it != mNodes.end());
		
		return it->second;
	}

	const std::map<glm::u32, BasicNode*>& BasicScene::getNodes() const
	{
		return mNodes;
	}

	const BasicNode& BasicScene::getRootNode() const
	{
		return mRootNode;
	}

	BasicNode& BasicScene::getRootNode()
	{
		return mRootNode;
	}
}
