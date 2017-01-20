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

	private:
	};
}