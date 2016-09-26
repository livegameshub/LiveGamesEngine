#ifndef _BASIC_NODE_H_
#define _BASIC_NODE_H_

#include "BasicElement.h"
#include "Transform.h"

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

		virtual void Update();
		virtual void Release();

		void AddComponent(BasicComponent* component);
		void AddChild(BasicNode* node);

		BasicComponent* GetComponent(glm::i32 type) const;
		BasicComponent* operator[](glm::i32 type) const;
		BasicComponent* RemoveComponent(glm::i32 type);
		
		BasicNode* GetChild(glm::u32 id) const;
		BasicNode* operator[](glm::u32 id) const;
		BasicNode* RemoveChild(glm::u32 id);
		
		inline const std::vector<BasicComponent*>& GetComponents() const;
		inline const std::vector<BasicNode*>& GetChildren() const;
		inline const Transform& GetTransform() const;
		inline Transform& GetTransform();

		inline void SetNodeType(glm::i32 type);
		inline glm::i32 GetNodeType() const;

		inline void SetEnabled(bool value);
		inline bool IsEnabled() const;

	protected:
		Transform mTransform;
		bool mIsEnabled;

	private:
		std::vector<BasicComponent*> mComponents;
		std::vector<BasicNode*> mChildren;

		glm::i32 mNodeType;
	};
}

#endif
