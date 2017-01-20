#pragma once
#include "Common.h"
#include "DirectXMath.h"

namespace thomas
{
	class THOMAS_API Camera
	{
	private:

	public:
		Camera(DirectX::XMVECTOR camPos, DirectX::XMVECTOR focusAt, float fov, float near, float far);
		DirectX::XMMATRIX CreateViewMatrix(DirectX::XMVECTOR camPos, DirectX::XMVECTOR focusAt);
		DirectX::XMMATRIX CreateProjMatrix(float fov, float near, float far);
		DirectX::XMMATRIX CreateViewProjMatrix();
		DirectX::XMMATRIX GetViewMatrix();
		DirectX::XMMATRIX GetProjMatrix();
		DirectX::XMMATRIX GetViewProjMatrix();

	private:
		DirectX::XMMATRIX m_viewMatrix; //ska det vara s_?
		DirectX::XMMATRIX m_projMatrix; //ska det vara s_?
		DirectX::XMMATRIX m_viewProjMatrix; //ska det vara s_?
	};
}