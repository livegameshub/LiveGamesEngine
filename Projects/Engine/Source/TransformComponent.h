#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_

#include "BasicComponent.h"

namespace ai
{
	class ENGINE_API TransformComponent : public BasicComponent
	{
	public:
		enum TransformFlag : glm::u32
		{
			NEW_POSITION = 1,
			NEW_ROTATION_SCALE_MATRIX = 2
		};

		TransformComponent();
		TransformComponent(const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale);

		~TransformComponent();

		void update() override;
		void reset() override;

		void translate(const glm::vec3& amount);
		void Scale(const glm::vec3& scale);

		void rotate(const glm::vec3& axis, glm::f32 angle);
		void rotate(const glm::vec3& angles);
		void rotateOnX(glm::f32 angle);
		void rotateOnY(glm::f32 angle);
		void rotateOnZ(glm::f32 angle);
	
		void setParentTransform(TransformComponent* transform);

		void setOrientation(const glm::quat& orientation);
		void setPosition(const glm::vec3& position);
		void setScale(const glm::vec3& scale);

		const glm::quat& getOrientation() const;
		const glm::vec3& getPosition() const;
		const glm::vec3& getScale() const;

		bool hasUniformScale() const;
		TransformComponent* getParentTransform() const;
		glm::mat4 getMatrix() const;

	private:
		TransformComponent* mParentTransform;

		bool mHasUniformScale;

		glm::mat4 mMatrix;
		glm::quat mOrientation;
		glm::vec3 mPosition;
		glm::vec3 mScale;
	};
}

#endif
