#pragma once
#include "Common.h"
#include "DirectXMath.h"

namespace thomas
{
	class THOMAS_API Camera
	{
	private:

	public:
		Camera(DirectX::XMFLOAT3 camPos, DirectX::XMFLOAT3 focusAt, float fov, float near, float far);
		DirectX::XMMATRIX CreateViewMatrix(DirectX::XMFLOAT3 camPos, DirectX::XMFLOAT3 focusAt);
		DirectX::XMMATRIX CreateProjMatrix(float fov, float near, float far);

	private:
	};
}