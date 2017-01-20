#include "Camera.h"
#include "Window.h"

thomas::Camera::Camera(DirectX::XMFLOAT3 camPos, DirectX::XMFLOAT3 focusAt, float fov, float viewNear, float viewFar)
{
	CreateProjMatrix(fov, viewNear, viewFar);
}

DirectX::XMMATRIX thomas::Camera::CreateViewMatrix(DirectX::XMFLOAT3 camPos, DirectX::XMFLOAT3 focusAt)
{
	//Call Thomas::Utils::Math::ToVector(camPos);
	//Call Thomas::Utils::Math::ToVector(focusAt);
	
	//return DirectX::XMMatrixLookAtLH(camPos, focusAt, )
}

DirectX::XMMATRIX thomas::Camera::CreateProjMatrix(float fov, float viewNear, float viewFar)
{
	return DirectX::XMMatrixPerspectiveFovLH(fov, Window::GetWidth() / Window::GetHeight(), viewNear, viewFar);

}
