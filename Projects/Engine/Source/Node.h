#ifndef _NODE_H_
#define _NODE_H_

#include "BasicElement.h"
#include "Transform.h"

namespace lg
{
	class Transform;

	class ENGINE_API Node : public BasicElement
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

		Node(glm::u32 id);
		Node(glm::u32 id, glm::i32 type);
		Node(glm::u32 id, glm::i32 type, const Flag& flag);
		Node(glm::u32 id, const Flag& flag);

		virtual ~Node();

		virtual void update();
		virtual void release();

		void addComponent(Component* component);
		void addChild(Node* node);

		Component* getComponent(glm::i32 type) const;
		Component* operator[](glm::i32 type) const;
		Component* removeComponent(glm::i32 type);
		
		Node* getChild(glm::u32 id) const;
		Node* operator[](glm::u32 id) const;
		Node* removeChild(glm::u32 id);
		
		const std::vector<Component*>& getComponents() const;
		const std::vector<Node*>& getChildren() const;
		const Transform& getTransform() const;
		Transform& getTransform();

		void setNodeType(glm::i32 type);
		glm::i32 getNodeType() const;

		void setEnabled(bool value);
		bool isEnabled() const;

	protected:
		Transform mTransform;
		bool mIsEnabled;

	private:
		std::vector<Component*> mComponents;
		std::vector<Node*> mChildren;

		glm::i32 mNodeType;
	};
}

#endif // _NODE_H_
