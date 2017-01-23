#pragma once
#include <DirectXMath.h>

namespace thomas
{
	namespace math
	{
			DirectX::XMVECTOR ToVector(DirectX::XMFLOAT3 *inVec);
			DirectX::XMFLOAT3 ToFloat(DirectX::XMVECTOR inVec);
	}
}
