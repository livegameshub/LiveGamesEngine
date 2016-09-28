#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "BasicNode.h"

namespace ai
{
	class ENGINE_API Camera : public BasicNode
	{
	public:
		enum CameraFlag : glm::u32
		{
			CAMERA_NEW_VIEW_MATRIX = 1,
			CAMERA_NEW_ORTHO_MATRIX = 2,
			CAMERA_NEW_PERSPECTIVE_MATRIX = 4
		};

		Camera(glm::u32 id);
		Camera(glm::u32 id, glm::f32 fov, glm::f32 near, glm::f32 far);

		~Camera();

		void Update() override;

		void RotateOnX(glm::f32 amount);
		void RotateOnY(glm::f32 amount);
		void RotateOnZ(glm::f32 amount);
		void MoveForward(glm::f32 amount);

		void LookAt(const glm::vec3& target);
		void MoveAt(const glm::vec3& position);
		
		bool HasCustomViewSize() const;
		void HasCustomViewSize(bool value);

		void SetFov(glm::f32 value);
		void SetNearPlane(glm::f32 value);
		void SetFarPlane(glm::f32 value);
		void SetViewSize(const glm::vec2& size);

		static const glm::mat4& GetOrthoMatrix();
		const glm::mat4& GetPerspecitiveMatrix() const;
		const glm::mat4& GetViewMatrix() const;

		const glm::vec2& GetViewSize() const;
		glm::f32 GetNearPlane() const;
		glm::f32 GetFarPlane() const;
		glm::f32 GetFov() const;

	private:
		bool mHasCustomViewSize;

		static glm::mat4 smOrthoMatrix;

		glm::mat4 mPerspectiveMatrix;
		glm::mat4 mViewMatrix;

		glm::vec2 mViewSize;

		glm::f32 mNearPlane;
		glm::f32 mFarPlane;
		glm::f32 mFov;
	};
}

#endif
