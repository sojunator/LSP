#include "Camera.h"
#include "Window.h"

thomas::Camera::Camera(DirectX::XMVECTOR camPos, DirectX::XMVECTOR focusAt, float fov, float viewNear, float viewFar)
{
	CreateViewMatrix(camPos, focusAt);
	CreateProjMatrix(fov, viewNear, viewFar);
}

DirectX::XMMATRIX thomas::Camera::CreateViewMatrix(DirectX::XMVECTOR camPos, DirectX::XMVECTOR focusAt)
{
	DirectX::XMVECTOR lookVector = DirectX::XMVectorSubtract(focusAt, camPos);
	DirectX::XMVECTOR tempUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR right = DirectX::XMVector3Cross(tempUp, lookVector);
	DirectX::XMVECTOR up =  DirectX::XMVector3Cross(lookVector, right);

	m_viewMatrix = DirectX::XMMatrixLookAtLH(camPos, focusAt, up);
}

DirectX::XMMATRIX thomas::Camera::CreateProjMatrix(float fov, float viewNear, float viewFar)
{
	m_projMatrix =  DirectX::XMMatrixPerspectiveFovLH(fov, Window::GetWidth() / Window::GetHeight(), viewNear, viewFar);
}

DirectX::XMMATRIX thomas::Camera::CreateViewProjMatrix()
{
	m_viewProjMatrix = DirectX::XMMatrixMultiply(m_viewMatrix, m_projMatrix);
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
