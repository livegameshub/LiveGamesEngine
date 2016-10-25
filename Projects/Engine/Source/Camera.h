#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Node.h"

namespace lg
{
	class ENGINE_API Camera : public Node
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

		void update() override;

		void rotateOnX(glm::f32 amount);
		void rotateOnY(glm::f32 amount);
		void rotateOnZ(glm::f32 amount);
		void moveForward(glm::f32 amount);

		void lookAt(const glm::vec3& target);
		void moveAt(const glm::vec3& position);
		
		bool hasCustomViewSize() const;
		void hasCustomViewSize(bool value);

		void setFov(glm::f32 value);
		void setNearPlane(glm::f32 value);
		void setFarPlane(glm::f32 value);
		void setViewSize(const glm::vec2& size);

		static const glm::mat4& getOrthoMatrix();
		const glm::mat4& getPerspecitiveMatrix() const;
		const glm::mat4& getViewMatrix() const;

		const glm::vec2& getViewSize() const;
		glm::f32 getNearPlane() const;
		glm::f32 getFarPlane() const;
		glm::f32 getFov() const;

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

#endif // _CAMERA_H_
