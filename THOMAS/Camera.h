#pragma once
#include "Common.h"
#include "DirectXMath.h"

namespace thomas
{
	class THOMAS_API Camera
	{
	private:
		void CreateViewMatrix(DirectX::XMVECTOR camPos, DirectX::XMVECTOR focusAt);
		void CreateProjMatrix(float fov, float near, float far);
		void CreateViewProjMatrix();
		void Update();
		
	public:
		Camera(DirectX::XMVECTOR camPos, DirectX::XMVECTOR focusAt, float fov, float near, float far);
		DirectX::XMMATRIX GetViewMatrix();
		DirectX::XMMATRIX GetProjMatrix();
		DirectX::XMMATRIX GetViewProjMatrix();
		DirectX::XMVECTOR GetCamPos();
		DirectX::XMVECTOR GetFocus();
		float GetFov();
		float GetNear();
		float GetFar();
		void SetCamPos(DirectX::XMVECTOR camPos);
		void SetFocus(DirectX::XMVECTOR focusAt);
		void SetFov(float fov);
		void SetNear(float viewNear);
		void SetFar(float viewFar);

	private:
		DirectX::XMMATRIX m_viewMatrix;
		DirectX::XMMATRIX m_projMatrix;
		DirectX::XMMATRIX m_viewProjMatrix;
		DirectX::XMVECTOR m_camPos;
		DirectX::XMVECTOR m_focusAt;
		float m_fov;
		float m_near;
		float m_far;
	};
}