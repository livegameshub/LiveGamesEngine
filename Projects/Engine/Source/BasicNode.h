#ifndef _BASIC_NODE_H_
#define _BASIC_NODE_H_

#include "BasicElement.h"
#include "TransformComponent.h"

namespace ai
{
	class ENGINE_API BasicNode : public BasicElement
	{
	public:
		enum NodeType : glm::i32
		{
			BASIC_NODE,
			CAMERA_NODE,
			MODEL_NODE,
			SPRITE_NODE,
			LIGHT_NODE
		};

		BasicNode(glm::u32 id);
		BasicNode(glm::u32 id, glm::i32 type);
		BasicNode(glm::u32 id, glm::i32 type, const Flag& flag);
		BasicNode(glm::u32 id, const Flag& flag);

		virtual ~BasicNode();

		virtual void update();
		virtual void release();

		void addComponent(BasicComponent* component);
		void addChild(BasicNode* node);

		BasicComponent* getComponent(glm::i32 type) const;
		BasicComponent* operator[](glm::i32 type) const;
		BasicComponent* removeComponent(glm::i32 type);
		
		BasicNode* getChild(glm::u32 id) const;
		BasicNode* operator[](glm::u32 id) const;
		BasicNode* removeChild(glm::u32 id);
		
		const std::vector<BasicComponent*>& getComponents() const;
		const std::vector<BasicNode*>& getChildren() const;
		const TransformComponent& getTransform() const;
		TransformComponent& getTransform();

		void setNodeType(glm::i32 type);
		glm::i32 getNodeType() const;

		void setEnabled(bool value);
		bool isEnabled() const;

	protected:
		TransformComponent mTransform;
		bool mIsEnabled;

	private:
		std::vector<BasicComponent*> mComponents;
		std::vector<BasicNode*> mChildren;

		glm::i32 mNodeType;
	};
}

#endif
