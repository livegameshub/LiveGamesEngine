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
	}

	void BasicScene::Release()
	{
	}

	void BasicScene::AddNode(BasicNode* node)
	{
	}

	BasicNode* BasicScene::RemoveNode(u32 id)
	{
	}

	BasicNode* BasicScene::operator[](u32 id) const
	{
	}

	BasicNode* BasicScene::GetNode(u32 id) const
	{
	}

	const std::map<u32, BasicNode*>& BasicScene::GetNodes() const
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
