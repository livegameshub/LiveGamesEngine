#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"

/* some useful constants */
const glm::vec3 VECTOR_UP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 VECTOR_RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 VECTOR_FORWARD = glm::vec3(0.0f, 0.0f, -1.0f);

namespace ai
{
	class ENGINE_API Transform : public Component
	{
	public:
		enum TransformFlag : glm::u32
		{
			NEW_POSITION = 1,
			NEW_ROTATION_SCALE_MATRIX = 2
		};

		Transform();
		Transform(const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale);

		~Transform();

		void update() override;
		void reset() override;

		void translate(const glm::vec3& amount);
		void Scale(const glm::vec3& scale);

		void rotate(const glm::vec3& axis, glm::f32 angle);
		void rotate(const glm::vec3& angles);
		void rotateOnX(glm::f32 angle);
		void rotateOnY(glm::f32 angle);
		void rotateOnZ(glm::f32 angle);
	
		void setParentTransform(Transform* transform);

		void setOrientation(const glm::quat& orientation);
		void setPosition(const glm::vec3& position);
		void setScale(const glm::vec3& scale);

		const glm::quat& getOrientation() const;
		const glm::vec3& getPosition() const;
		const glm::vec3& getScale() const;

		bool hasUniformScale() const;
		Transform* getParentTransform() const;
		glm::mat4 getMatrix() const;

	private:
		Transform* mParentTransform;

		bool mHasUniformScale;

		glm::mat4 mMatrix;
		glm::quat mOrientation;
		glm::vec3 mPosition;
		glm::vec3 mScale;
	};
}

#endif // _TRANSFORM_H_
