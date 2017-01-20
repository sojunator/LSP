#include "Camera.h"
#include "Window.h"

thomas::Camera::Camera(DirectX::XMVECTOR camPos, DirectX::XMVECTOR focusAt, float fov, float viewNear, float viewFar)
{
	m_camPos = camPos;
	m_focusAt = focusAt;
	m_fov = fov;
	m_near = viewNear;
	m_far = viewFar;

	Update();
}

void thomas::Camera::CreateViewMatrix(DirectX::XMVECTOR camPos, DirectX::XMVECTOR focusAt)
{
	DirectX::XMVECTOR lookVector = DirectX::XMVectorSubtract(focusAt, camPos);
	DirectX::XMVECTOR tempUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR right = DirectX::XMVector3Cross(tempUp, lookVector);
	DirectX::XMVECTOR up =  DirectX::XMVector3Cross(lookVector, right);

	m_viewMatrix = DirectX::XMMatrixLookAtLH(camPos, focusAt, up);
}

void thomas::Camera::CreateProjMatrix(float fov, float viewNear, float viewFar)
{
	m_projMatrix =  DirectX::XMMatrixPerspectiveFovLH(fov, Window::GetWidth() / Window::GetHeight(), viewNear, viewFar);
}

void thomas::Camera::CreateViewProjMatrix()
{
	m_viewProjMatrix = DirectX::XMMatrixMultiply(m_viewMatrix, m_projMatrix);
}

void thomas::Camera::Update()
{
	CreateViewMatrix(m_camPos, m_focusAt);
	CreateProjMatrix(m_fov, m_near, m_far);
	CreateViewProjMatrix();
}

DirectX::XMMATRIX thomas::Camera::GetViewMatrix()
{
	return m_viewMatrix;
}

DirectX::XMMATRIX thomas::Camera::GetProjMatrix()
{
	return m_projMatrix;
}

DirectX::XMMATRIX thomas::Camera::GetViewProjMatrix()
{
	return m_viewProjMatrix;
}

DirectX::XMVECTOR thomas::Camera::GetCamPos()
{
	return m_camPos;
}

DirectX::XMVECTOR thomas::Camera::GetFocus()
{
	return m_focusAt;
}

float thomas::Camera::GetFov()
{
	return m_fov;
}

float thomas::Camera::GetNear()
{
	return m_near;
}

float thomas::Camera::GetFar()
{
	return m_far;
}

void thomas::Camera::SetCamPos(DirectX::XMVECTOR camPos)
{
	m_camPos = camPos;
	CreateViewMatrix(m_camPos, m_focusAt);
	CreateViewProjMatrix();
}

void thomas::Camera::SetFocus(DirectX::XMVECTOR focusAt)
{
	m_focusAt = focusAt;
	CreateViewMatrix(m_camPos, m_focusAt);
	CreateViewProjMatrix();
}

void thomas::Camera::SetFov(float fov)
{
	m_fov = fov;
	CreateProjMatrix(m_fov, m_near, m_far);
	CreateViewProjMatrix();
}

void thomas::Camera::SetNear(float viewNear)
{
	m_near = viewNear;
	CreateProjMatrix(m_fov, m_near, m_far);
	CreateViewProjMatrix();
}

void thomas::Camera::SetFar(float viewFar)
{
	m_far = viewFar;
	CreateProjMatrix(m_fov, m_near, m_far);
	CreateViewProjMatrix();
}
