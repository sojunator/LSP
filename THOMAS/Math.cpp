#include "Math.h"

thomas::utils::Math::Math()
{
}

thomas::utils::Math::~Math()
{
}

DirectX::XMVECTOR thomas::utils::Math::ToVector(DirectX::XMFLOAT3 *inVec)
{
	return DirectX::XMVECTOR(DirectX::XMLoadFloat3(inVec));
}

DirectX::XMFLOAT3 thomas::utils::Math::ToFloat(DirectX::XMVECTOR inVec)
{
	DirectX::XMFLOAT3 temp;
	DirectX::XMStoreFloat3(&temp, inVec);
	return temp;
}
