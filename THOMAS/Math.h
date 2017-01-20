#pragma once
#include <DirectXMath.h>

namespace thomas
{
	namespace utils
	{
		class Math
		{
		public:
			Math();
			~Math();

			DirectX::XMVECTOR ToVector(DirectX::XMFLOAT3 *inVec);
			DirectX::XMFLOAT3 ToFloat(DirectX::XMVECTOR inVec);

		private:

		};
	}
}
