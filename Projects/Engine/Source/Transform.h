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
		Transform();
		~Transform();

		void Update() override;
		void Reset() override;

		inline void SetParentTransform(Transform* transform);

		void SetOrientation(const Quaternion& orientation);
		void SetPosition(const Vector3& position);
		void SetScale(const Vector3& scale);

		inline const Quaternion& GetOrientation() const;
		inline const Vector3& GetPosition() const;
		inline const Vector3& GetScale() const;

		inline Transform* GetParentTransform() const;
		inline Matrix4 GetMatrix() const;

	private:
		Transform* mParentTransform;

		Matrix4 mMatrix;

		Quaternion mOrientation;
		Vector3 mPosition;
		Vector3 mScale;
	};
}

#endif
