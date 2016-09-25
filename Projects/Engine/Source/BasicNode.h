#ifndef _BASIC_NODE_H_
#define _BASIC_NODE_H_

#include "BasicElement.h"
#include "Transform.h"

namespace ai
{
	class ENGINE_API BasicNode : public BasicElement
	{
	public:
		enum NodeType : i32
		{
			BASIC_NODE,
			CAMERA_NODE,
			MODEL_NODE,
			SPRITE_NODE,
			LIGHT_NODE
		};

		BasicNode(u32 id);
		BasicNode(u32 id, i32 type);
		BasicNode(u32 id, i32 type, const Flag& flag);
		BasicNode(u32 id, const Flag& flag);

		virtual ~BasicNode();

		virtual void Update();
		virtual void Release();

		void AddComponent(BasicComponent* component);
		void AddChild(BasicNode* node);

		BasicComponent* GetComponent(i32 type) const;
		BasicComponent* operator[](i32 type) const;
		BasicComponent* RemoveComponent(i32 type);
		
		BasicNode* GetChild(u32 id) const;
		BasicNode* operator[](u32 id) const;
		BasicNode* RemoveChild(u32 id);
		
		inline const std::vector<BasicComponent*>& GetComponents() const;
		inline const std::vector<BasicNode*>& GetChildren() const;
		inline const Transform& GetTransform() const;
		inline Transform& GetTransform();

		inline void SetNodeType(i32 type);
		inline i32 GetNodeType() const;

		inline void SetEnabled(bool value);
		inline bool IsEnabled() const;

	protected:
		Transform mTransform;
		bool mIsEnabled;

	private:
		std::vector<BasicComponent*> mComponents;
		std::vector<BasicNode*> mChildren;

		i32 mNodeType;
	};
}

#endif
