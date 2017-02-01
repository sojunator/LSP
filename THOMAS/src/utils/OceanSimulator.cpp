#include "OceanSimulator.h"
#include "d3d.h"

namespace thomas
{
	namespace utils
	{
		void thomas::utils::OceanSimulator::InitHeightMap(math::Vector2 * outH0, float * outOmega)
		{
			
		}

		float OceanSimulator::Gauss()
		{
			float u1 = rand() / (float)RAND_MAX;
			float u2 = rand() / (float)RAND_MAX;
			if (u1 < 1e-6f)
				u1 = 1e-6f;
			return (sqrtf(-2 * logf(u1))*cosf(2 * math::PI*u2));
		}

		float OceanSimulator::Phillips(math::Vector2 k, math::Vector2 w, float v, float a, float dir_depend)
		{
			// largest possible wave from constant wind of velocity v
			float l = v * v / m_settings.gravity;
			// damp out waves with very small length w << l
			float damp = l / 1000;

			float kSqr = k.x * k.x + k.y * w.y;
			float kCos = k.x * w.x + k.y * w.y;
			float phillips = a * expf(-1 / (l * l * kSqr)) / (kSqr * kSqr * kSqr) * (kCos * kCos);

			// filter out waves moving opposite to wind
			if (kCos < 0)
				phillips *= dir_depend;

			// damp out waves with very small length w << l
			return phillips * expf(-kSqr * damp * damp);
		}

		thomas::utils::OceanSimulator::OceanSimulator(OceanSettings & settings)
		{
			m_settings = settings;

			// Height map H(0)
			int heightMapSize = (settings.mapDimension + 4) * (settings.mapDimension + 1);
			math::Vector2* h0Data = new math::Vector2[heightMapSize * sizeof(math::Vector2)];
			float* omegaData = new float[heightMapSize * sizeof(float)];
			InitHeightMap(h0Data, omegaData);

			// This value should be (hmap_dim / 2 + 1) * hmap_dim, but we use full sized buffer here for simplicity.
			int inputHalfSize = settings.mapDimension*settings.mapDimension;
			int outputSize = settings.mapDimension*settings.mapDimension;

			// For filling the buffer with zeroes.
			char* zeroData = new char[3 * outputSize * sizeof(float) * 2];
			memset(zeroData, 0, 3 * outputSize * sizeof(float) * 2);

			// RW buffer allocations
			// H0
			UINT float2Stride = 2 * sizeof(float);
			D3d::CreateBufferAndUAV(h0Data, heightMapSize * float2Stride, float2Stride, m_bufferH0, m_uavH0, m_srvH0);

			// Notice: The following 3 buffers should be half sized buffer because of conjugate symmetric input. But
			// we use full sized buffers due to the CS4.0 restriction.

			// Put H(t), Dx(t) and Dy(t) into one buffer because CS4.0 allows only 1 UAV at a time
			D3d::CreateBufferAndUAV(zeroData, 3 * inputHalfSize * float2Stride, float2Stride, m_bufferHT, m_uavHT, m_srvHT);

			// omega
			D3d::CreateBufferAndUAV(omegaData, heightMapSize * sizeof(float), sizeof(float), m_bufferOmega, m_uavOmega, m_srvOmega);

			// Notice: The following 3 should be real number data. But here we use the complex numbers and C2C FFT
			// due to the CS4.0 restriction.
			// Put Dz, Dx and Dy into one buffer because CS4.0 allows only 1 UAV at a time
			D3d::CreateBufferAndUAV(zeroData, 3 * outputSize * float2Stride, float2Stride, m_bufferDxyz, m_uavDxyz, m_srvDxyz);


			delete zeroData;
			delete h0Data;
			delete omegaData;

			// D3D11 Textures
			D3d::CreateTextureAndViews(settings.mapDimension, settings.mapDimension, DXGI_FORMAT_R32G32B32A32_FLOAT, m_displacementMap, m_displacmentSRV, m_displacementRTV);
			D3d::CreateTextureAndViews(settings.mapDimension, settings.mapDimension, DXGI_FORMAT_R16G16B16A16_FLOAT, m_normalMap, m_normalSRV, m_normalRTV);


		}

		thomas::utils::OceanSimulator::OceanSimulator()
		{
		}

		void thomas::utils::OceanSimulator::Update()
		{
		}

		ID3D11ShaderResourceView * thomas::utils::OceanSimulator::GetDisplacementMap()
		{
			return nullptr;
		}

		ID3D10ShaderResourceView* thomas::utils::OceanSimulator::GetNormalMap()
		{
			return nullptr;
		}

		OceanSimulator::OceanSettings & thomas::utils::OceanSimulator::GetSettings()
		{
			// TODO: insert return statement here
		}

	}
}

