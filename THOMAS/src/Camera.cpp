#include "Camera.h"
#include "Window.h"
namespace thomas
{
	Camera::Camera(math::Vector3 camPos, math::Vector3 focusAt, float fov, float nearPlane, float farPlane)
	{
		m_camPos = camPos;
		m_focusAt = focusAt;
		m_camDir = focusAt - camPos;
		m_fov = fov;
		m_near = nearPlane;
		m_far = farPlane;

		Update();
	}

	void Camera::MoveCamera(math::Vector3 direction)
	{
		m_camPos += 0.20 * direction;
	}

	void Camera::RotateCamera(math::Vector3 rotate)
	{
		math::Matrix rotation = math::Matrix::CreateFromYawPitchRoll(rotate.y, rotate.y, rotate.z);
		m_camDir = math::Vector3::Transform(m_camDir, rotation);
	}

	void Camera::CreateViewMatrix(math::Vector3 camPos, math::Vector3 focusAt)
	{
		math::Vector3 lookVec = focusAt - camPos;
		math::Vector3 tempUp = math::Vector3(0.0f, 1.0f, 0.0f);
		math::Vector3 right = tempUp.Cross(lookVec);
		math::Vector3 up = lookVec.Cross(right);

		m_viewMatrix = math::Matrix::CreateLookAt(camPos, focusAt, up);
	}

	void Camera::CreateProjMatrix(float fov, float viewNear, float viewFar)
	{
		m_projMatrix = math::Matrix::CreatePerspectiveFieldOfView(fov, Window::GetWidth() / Window::GetHeight(), viewNear, viewFar);
	}

	void Camera::CreateViewProjMatrix()
	{
		m_viewProjMatrix = m_viewMatrix * m_projMatrix;		//Need to be tested
	}

	void Camera::Update()
	{
		CreateViewMatrix(m_camPos, m_focusAt);
		CreateProjMatrix(m_fov, m_near, m_far);
		CreateViewProjMatrix();
	}

	math::Matrix Camera::GetViewMatrix()
	{
		return m_viewMatrix;
	}

	math::Matrix Camera::GetProjMatrix()
	{
		return m_projMatrix;
	}

	math::Matrix Camera::GetViewProjMatrix()
	{
		return m_viewProjMatrix;
	}

	math::Vector3 Camera::GetCamPos()
	{
		return m_camPos;
	}

	math::Vector3 Camera::GetCamDirection()
	{
		return m_camDir;
	}

	math::Vector3 Camera::GetFocus()
	{
		return m_focusAt;
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

	void Camera::SetCamPos(math::Vector3 camPos)
	{
		m_camPos = camPos;
		CreateViewMatrix(m_camPos, m_focusAt);
		CreateViewProjMatrix();
	}

	void Camera::SetCamDirection(math::Vector3 camDir)
	{
		m_camDir = camDir;
	}

	void Camera::SetFocus(math::Vector3 focusAt)
	{
		m_focusAt = focusAt;
		CreateViewMatrix(m_camPos, m_focusAt);
		CreateViewProjMatrix();
	}

	void Camera::SetFov(float fov)
	{
		m_fov = fov;
		CreateProjMatrix(m_fov, m_near, m_far);
		CreateViewProjMatrix();
	}

	void Camera::SetNear(float viewNear)
	{
		m_near = viewNear;
		CreateProjMatrix(m_fov, m_near, m_far);
		CreateViewProjMatrix();
	}

	void Camera::SetFar(float viewFar)
	{
		m_far = viewFar;
		CreateProjMatrix(m_fov, m_near, m_far);
		CreateViewProjMatrix();
	}
}