#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "BasicComponent.h"
#include "Matrix4.h"
#include "Vector3.h"
#include "Quaternion.h"

namespace ai
{
	class ENGINE_API Transform : public BasicComponent
	{
	public:
		enum TransformFlag : u32
		{
			NEW_POSITION = 1,
			NEW_ROTATION_SCALE_MATRIX = 2
		};

		Transform();
		Transform(const Vector3& position, const Quaternion& orientation, const Vector3& scale);
		~Transform();

		void Update() override;
		void Reset() override;

		void Translate(const Vector3& amount);
		void Scale(const Vector3& scale);

		void Rotate(const Vector3& axis, f32 angle);
		void Rotate(const Vector3& angles);
		void RotateOnX(f32 angle);
		void RotateOnY(f32 angle);
		void RotateOnZ(f32 angle);
	
		inline void SetParentTransform(Transform* transform);

		void SetOrientation(const Quaternion& orientation);
		void SetPosition(const Vector3& position);
		void SetScale(const Vector3& scale);

		inline const Quaternion& GetOrientation() const;
		inline const Vector3& GetPosition() const;
		inline const Vector3& GetScale() const;

		inline bool HasUniformScale() const;
		inline Transform* GetParentTransform() const;
		inline Matrix4 GetMatrix() const;

	private:
		Transform* mParentTransform;

		Matrix4 mMatrix;

		Quaternion mOrientation;
		Vector3 mPosition;
		Vector3 mScale;

		bool mHasUniformScale;
	};
}

#endif
