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
				m_projMatrix = math::Matrix::CreatePerspectiveFieldOfView(m_fov, m_viewport.AspectRatio(), m_near, m_far);
			}

			Camera::Camera(GameObject* gameObject): Component("CameraObject", gameObject)
			{
				m_fov = 70;
				m_near = 0.1;
				m_far = 1000;
				m_viewport = math::Viewport(0, 0, Window::GetWidth(), Window::GetHeight());
				m_skybox = NULL;
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

			math::Viewport Camera::GetViewport()
			{
				return m_viewport;
			}

			void Camera::SetViewport(math::Viewport viewport)
			{
				m_viewport = viewport;
				UpdateProjMatrix();
			}

			void Camera::SetViewport(float x, float y, float width, float height)
			{
				SetViewport(math::Viewport(x, y, width, height));
			}

			float Camera::GetAspectRatio()
			{
				return m_viewport.AspectRatio();
			}

			void Camera::SetSkybox(std::string path, std::string shaderName)
			{
				m_skybox = new graphics::Skybox(path, shaderName);
			}

			void Camera::BindSkybox()
			{
				if (m_skybox)
				{
					math::Matrix mvpMatrix = (m_gameObject->m_transform->GetWorldMatrix()*GetViewProjMatrix()).Transpose();
					m_skybox->Bind(GetViewMatrix(), mvpMatrix);
				}
					
			}

			void Camera::UnbindSkybox()
			{
				if (m_skybox)
					m_skybox->Unbind();
			}


		}
	}
}