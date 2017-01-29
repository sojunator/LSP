#include "Camera.h"
#include "../../Window.h"
#include "../GameObject.h"
namespace thomas
{
	namespace object
	{
		namespace component
		{
			void Camera::UpdateProjMatrix()
			{
				m_projMatrix = math::Matrix::CreatePerspectiveFieldOfView(m_fov, m_aspectRatio, m_near, m_far);
			}

			Camera::Camera(GameObject* gameObject): Component("CameraObject", gameObject)
			{
				m_fov = 70;
				m_near = 0.1;
				m_far = 10;
				m_aspectRatio = 1;
				UpdateProjMatrix();
			}

			math::Matrix Camera::GetProjMatrix()
			{
				return m_projMatrix;
			}

			math::Matrix Camera::GetViewMatrix()
			{
				math::Matrix viewMatrix =  m_gameObject->m_transform->GetWorldMatrix();
				return viewMatrix.Invert();
			}

			math::Matrix Camera::GetViewProjMatrix()
			{
				return GetViewMatrix() * m_projMatrix;
			}

			math::Vector3 Camera::GetPosition()
			{
				return m_gameObject->m_transform->GetPosition();
			}

			float Camera::GetFov()
			{
				return m_fov;
			}

			float Camera::GetNear()
			{
				return m_near;
			}

			float Camera::GetFar()
			{
				return m_far;
			}

			void Camera::SetFov(float fov)
			{
				m_fov = fov;
				UpdateProjMatrix();
			}

			void Camera::SetNear(float viewNear)
			{
				m_near = viewNear;
				UpdateProjMatrix();
			}

			void Camera::SetFar(float viewFar)
			{
				m_far = viewFar;
				UpdateProjMatrix();
			}

			float Camera::GetAspectRatio()
			{
				return m_aspectRatio;
			}

			void Camera::SetAspectRatio(float aspectRatio)
			{
				m_aspectRatio = aspectRatio;
			}

		}
	}
}