#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "BasicComponent.h"

namespace ai
{
	class ENGINE_API Transform : public BasicComponent
	{
	public:
		const glm::vec3 VECTOR_UP = glm::vec3(1.0f, 0.0f, 0.0f);
		const glm::vec3 VECTOR_RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
		const glm::vec3 VECTOR_FORWARD = glm::vec3(0.0f, 0.0f, -1.0f);

		enum TransformFlag : glm::u32
		{
			NEW_POSITION = 1,
			NEW_ROTATION_SCALE_MATRIX = 2
		};

		Transform();
		Transform(const glm::vec3& position, const glm::quat& orientation, const glm::vec3& scale);
		~Transform();

		void Update() override;
		void Reset() override;

		void Translate(const glm::vec3& amount);
		void Scale(const glm::vec3& scale);

		void Rotate(const glm::vec3& axis, glm::f32 angle);
		void Rotate(const glm::vec3& angles);
		void RotateOnX(glm::f32 angle);
		void RotateOnY(glm::f32 angle);
		void RotateOnZ(glm::f32 angle);
	
		inline void SetParentTransform(Transform* transform);

		void SetOrientation(const glm::quat& orientation);
		void SetPosition(const glm::vec3& position);
		void SetScale(const glm::vec3& scale);

		inline const glm::quat& GetOrientation() const;
		inline const glm::vec3& GetPosition() const;
		inline const glm::vec3& GetScale() const;

		inline bool HasUniformScale() const;
		inline Transform* GetParentTransform() const;
		inline glm::mat4 GetMatrix() const;

	private:
		Transform* mParentTransform;

		glm::mat4 mMatrix;

		glm::quat mOrientation;
		glm::vec3 mPosition;
		glm::vec3 mScale;

		bool mHasUniformScale;
	};
}

#endif
