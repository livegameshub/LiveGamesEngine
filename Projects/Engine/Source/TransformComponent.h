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
		void Reset() override;

		void translate(const glm::vec3& amount);
		void Scale(const glm::vec3& scale);

		void Rotate(const glm::vec3& axis, glm::f32 angle);
		void Rotate(const glm::vec3& angles);
		void RotateOnX(glm::f32 angle);
		void RotateOnY(glm::f32 angle);
		void RotateOnZ(glm::f32 angle);
	
		void SetParentTransform(TransformComponent* transform);

		void SetOrientation(const glm::quat& orientation);
		void SetPosition(const glm::vec3& position);
		void SetScale(const glm::vec3& scale);

		const glm::quat& GetOrientation() const;
		const glm::vec3& GetPosition() const;
		const glm::vec3& GetScale() const;

		bool HasUniformScale() const;
		TransformComponent* GetParentTransform() const;
		glm::mat4 GetMatrix() const;

	private:
		TransformComponent* mParentTransform;

		glm::mat4 mMatrix;

		glm::quat mOrientation;
		glm::vec3 mPosition;
		glm::vec3 mScale;

		bool mHasUniformScale;
	};
}

#endif
