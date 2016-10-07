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

		virtual void init();
		virtual void update();
		virtual void release();
		
		void addNode(BasicNode* node);

		BasicNode* removeNode(glm::u32 id);
		BasicNode* operator[](glm::u32 id) const;
		BasicNode* getNode(glm::u32 id) const;

		const std::map<glm::u32, BasicNode*>& getNodes() const;
		const BasicNode& getRootNode() const;
		BasicNode& getRootNode();

	protected:
		BasicNode mRootNode;

	private:
		std::map<glm::u32, BasicNode*> mNodes;
	};
}

#endif
