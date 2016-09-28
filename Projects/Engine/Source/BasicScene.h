#ifndef _BASIC_SCENE_H_
#define _BASIC_SCENE_H_

#include "BasicNode.h"

namespace ai
{
	class ENGINE_API BasicScene
	{
	public:
		BasicScene();

		virtual ~BasicScene();

		virtual void Init();
		virtual void Update();
		virtual void Release();

		void AddNode(BasicNode* node);

		BasicNode* RemoveNode(glm::u32 id);
		BasicNode* operator[](glm::u32 id) const;
		BasicNode* GetNode(glm::u32 id) const;

		inline const std::map<glm::u32, BasicNode*>& GetNodes() const;
		inline const BasicNode& GetRootNode() const;
		inline BasicNode& GetRootNode();

	protected:
		BasicNode mRootNode;

	private:
		std::map<glm::u32, BasicNode*> mNodes;
	};
}

#endif
