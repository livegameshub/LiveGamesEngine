#ifndef _NODE_H_
#define _NODE_H_

#include "Object.h"
#include "Transform.h"

namespace lg
{
	class Transform;

	class ENGINE_API Node : public Object
	{
	public:
		enum NodeFlag : glm::i32
		{
			IS_ENABLED = 1,
			IS_VISIBLE = 2
		};

		enum NodeType : glm::i32
		{
			BASIC_NODE,
			CAMERA_NODE,
			RENDERABLE_NODE,
			SPRITE_NODE,
			LIGHT_NODE
		};

		Node(glm::u32 id);
		Node(glm::u32 id, glm::i32 type);
		Node(glm::u32 id, glm::i32 type, const Flag& flag);
		Node(glm::u32 id, const Flag& flag);

		virtual ~Node();

		virtual void update();
		virtual void release();
		
		/* nodes */

		void addChild(Node* node);
		Node* getChild(glm::u32 id) const;
		Node* operator[](glm::u32 id) const;
		Node* removeChild(glm::u32 id);

		/* components */

		void addComponent(Component* component);
		Component* getComponent(glm::i32 type) const;
		Component* operator[](glm::i32 type) const;
		Component* removeComponent(glm::i32 type);
		
		const std::vector<Component*>& getComponents() const;
		const std::vector<Node*>& getChildren() const;
		const Transform& getTransform() const;
		Transform& getTransform();

		void setNodeType(glm::i32 type);
		glm::i32 getNodeType() const;

		bool isVisible() const;
		bool isEnabled() const;

	protected:
		Transform mTransform;

	private:
		std::vector<Component*> mComponents;
		std::vector<Node*> mChildren;

		glm::i32 mNodeType;
	};
}

#endif // _NODE_H_
