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

		inline void SetType(i32 type);
		inline i32 GetType() const;

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
