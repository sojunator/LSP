#include "OceanSimulator.h"
#include "d3d.h"
#include "../graphics/Shader.h"

namespace thomas
{
	namespace utils
	{
		void thomas::utils::OceanSimulator::InitHeightMap(math::Vector2 * outH0, float * outOmega)
		{
			float halfSqrt2 = 0.7071068f;
			int i, j;
			math::Vector2 k, kn;

			m_settings.windDir.Normalize();
			math::Vector2 windDir = m_settings.windDir;

			float a = m_settings.waveAmplitude * 1e-7f;	// It is too small. We must scale it for editing.
			float v = m_settings.windSpeed;

			//Init random generator
			srand(0);

			for (i = 0; i <= m_settings.mapDimension; i++)
			{
				// K is wave-vector, range [-|DX/W, |DX/W], [-|DY/H, |DY/H]
				k.y = (-m_settings.mapDimension / 2.0f + i) * (2 * math::PI / m_settings.patchLength);

				for (j = 0; j <= m_settings.mapDimension; i++)
				{
					k.x = (-m_settings.mapDimension / 2.0f + j) * (2 * math::PI / m_settings.patchLength);

					float phil = (k.x == 0 && k.y == 0) ? 0 : sqrtf(Phillips(k, windDir, v, a, m_settings.windDependency));
					outH0[i*(m_settings.mapDimension + 4) + j].x = float(phil*Gauss()*halfSqrt2);
					outH0[i*(m_settings.mapDimension + 4) + j].y = float(phil*Gauss()*halfSqrt2);

					// The angular frequency is following the dispersion relation:
					//            out_omega^2 = g*k
					// The equation of Gerstner wave:
					//            x = x0 - K/k * A * sin(dot(K, x0) - sqrt(g * k) * t), x is a 2D vector.
					//            z = A * cos(dot(K, x0) - sqrt(g * k) * t)
					// Gerstner wave shows that a point on a simple sinusoid wave is doing a uniform circular
					// motion with the center (x0, y0, z0), radius A, and the circular plane is parallel to
					// vector K.
					outOmega[i * (m_settings.mapDimension + 4) + j] = sqrtf(m_settings.gravity * sqrtf(k.x * k.x + k.y * k.y));
				}
			}
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

		void OceanSimulator::FFT512x512CreatePlan(CSFFT512x512Plan * plan, UINT slices)
		{
		}

		void OceanSimulator::FFT512x512DestroyPlan(CSFFT512x512Plan * plan)
		{
		}

		void OceanSimulator::FFT512x512Calc(CSFFT512x512Plan * plan, ID3D11UnorderedAccessView * UAVDest, ID3D11ShaderResourceView * SRVDest, ID3D11ShaderResourceView * SRVSrc)
		{
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


			// Samplers
			D3D11_SAMPLER_DESC sam_desc;
			sam_desc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
			sam_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			sam_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			sam_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			sam_desc.MipLODBias = 0;
			sam_desc.MaxAnisotropy = 1;
			sam_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			sam_desc.BorderColor[0] = 1.0f;
			sam_desc.BorderColor[1] = 1.0f;
			sam_desc.BorderColor[2] = 1.0f;
			sam_desc.BorderColor[3] = 1.0f;
			sam_desc.MinLOD = -FLT_MAX;
			sam_desc.MaxLOD = FLT_MAX;
			ThomasCore::GetDevice()->CreateSamplerState(&sam_desc, &m_pointSamplerState);


			// Compute shaders
			ID3DBlob* blobUpdateSpectrumCS = NULL;

			blobUpdateSpectrumCS = graphics::Shader::Compile("ocean_simulator_cs.hlsl", "cs_4_0", "UpdateSpectrumCS");

			if (blobUpdateSpectrumCS)
			{
				ThomasCore::GetDevice()->CreateComputeShader(blobUpdateSpectrumCS->GetBufferPointer(), blobUpdateSpectrumCS->GetBufferSize(), NULL, &m_updateSpectrumCS);
				blobUpdateSpectrumCS->Release();
			}
			// Vertex & pixel shaders
			ID3DBlob* blobQuadVS = NULL;
			ID3DBlob* blobUpdateDisplacementPS = NULL;
			ID3DBlob* blobGenGradientFoldingPS = NULL;

			blobQuadVS = graphics::Shader::Compile("ocean_simulator_vs_ps.hlsl", "vs_4_0", "QuadVS");
			blobUpdateDisplacementPS = graphics::Shader::Compile("ocean_simulator_vs_ps.hlsl", "ps_4_0", "UpdateDisplacementPS");
			blobGenGradientFoldingPS = graphics::Shader::Compile("ocean_simulator_vs_ps.hlsl", "ps_4_0", "GenGradientFoldingPS");

			if (blobQuadVS)
			{
				ThomasCore::GetDevice()->CreateVertexShader(blobQuadVS->GetBufferPointer(), blobQuadVS->GetBufferSize(), NULL, &m_quadVS);
				
			}
			if (blobUpdateDisplacementPS)
			{
				ThomasCore::GetDevice()->CreatePixelShader(blobUpdateDisplacementPS->GetBufferPointer(), blobUpdateDisplacementPS->GetBufferSize(), NULL, &m_updateDisplacementPS);
				blobUpdateDisplacementPS->Release();
			}
			if (blobGenGradientFoldingPS)
			{
				ThomasCore::GetDevice()->CreatePixelShader(blobGenGradientFoldingPS->GetBufferPointer(), blobGenGradientFoldingPS->GetBufferSize(), NULL, &m_genNormalsPS);
				blobGenGradientFoldingPS->Release();
			}

			// Input layout
			D3D11_INPUT_ELEMENT_DESC quadLayoutDesc[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			if (blobQuadVS)
			{
				ThomasCore::GetDevice()->CreateInputLayout(quadLayoutDesc, 1, blobQuadVS->GetBufferPointer(), blobQuadVS->GetBufferSize(), &m_quadLayout);
			}

			// Quad vertex buffer
			D3D11_BUFFER_DESC vbDesc;
			vbDesc.ByteWidth = 4 * sizeof(math::Vector4);
			vbDesc.Usage = D3D11_USAGE_IMMUTABLE;
			vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vbDesc.CPUAccessFlags = 0;
			vbDesc.MiscFlags = 0;

			float quadVerts[] =
			{
				-1, -1, 0, 1,
				-1,  1, 0, 1,
				1, -1, 0, 1,
				1,  1, 0, 1,
			};
			D3D11_SUBRESOURCE_DATA init_data;
			init_data.pSysMem = &quadVerts[0];
			init_data.SysMemPitch = 0;
			init_data.SysMemSlicePitch = 0;

			ThomasCore::GetDevice()->CreateBuffer(&vbDesc, &init_data, &m_pQuadVertexBuffer);
			

			// Constant buffers
			UINT actual_dim = settings.mapDimension;
			UINT input_width = actual_dim + 4;
			// We use full sized data here. The value "output_width" should be actual_dim/2+1 though.
			UINT output_width = actual_dim;
			UINT output_height = actual_dim;
			UINT dtx_offset = actual_dim * actual_dim;
			UINT dty_offset = actual_dim * actual_dim * 2;
			UINT immutable_consts[] = { actual_dim, input_width, output_width, output_height, dtx_offset, dty_offset };
			D3D11_SUBRESOURCE_DATA init_cb0 = { &immutable_consts[0], 0, 0 };


			D3D11_BUFFER_DESC cb_desc;
			cb_desc.Usage = D3D11_USAGE_IMMUTABLE;
			cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cb_desc.CPUAccessFlags = 0;
			cb_desc.MiscFlags = 0;
			cb_desc.ByteWidth = (((sizeof(immutable_consts)) + 15) / 16 * 16);
			ThomasCore::GetDevice()->CreateBuffer(&cb_desc, &init_cb0, &m_immutableCB);

			ID3D11Buffer* cbs[1] = { m_immutableCB };
			ThomasCore::GetDeviceContext()->CSSetConstantBuffers(0, 1, cbs);
			ThomasCore::GetDeviceContext()->PSSetConstantBuffers(0, 1, cbs);

			cb_desc.Usage = D3D11_USAGE_DYNAMIC;
			cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cb_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cb_desc.MiscFlags = 0;
			cb_desc.ByteWidth = (((sizeof(float)*3) + 15) / 16 * 16);
			ThomasCore::GetDevice()->CreateBuffer(&cb_desc, NULL, &m_perFrameCB);

			// FFT
			FFT512x512CreatePlan(&m_fftPlan, 3);

		}

		thomas::utils::OceanSimulator::~OceanSimulator()
		{
			FFT512x512DestroyPlan(&m_fftPlan);

			SAFE_RELEASE(m_bufferH0);
			SAFE_RELEASE(m_bufferOmega);
			SAFE_RELEASE(m_bufferHT);
			SAFE_RELEASE(m_bufferDxyz);

			SAFE_RELEASE(m_pointSamplerState);

			SAFE_RELEASE(m_pQuadVertexBuffer);

			SAFE_RELEASE(m_uavH0);
			SAFE_RELEASE(m_uavOmega);
			SAFE_RELEASE(m_uavHT);
			SAFE_RELEASE(m_uavDxyz);

			SAFE_RELEASE(m_srvH0);
			SAFE_RELEASE(m_srvOmega);
			SAFE_RELEASE(m_srvHT);
			SAFE_RELEASE(m_uavDxyz);

			SAFE_RELEASE(m_displacementMap);
			SAFE_RELEASE(m_displacmentSRV);
			SAFE_RELEASE(m_displacementRTV);

			SAFE_RELEASE(m_normalMap);
			SAFE_RELEASE(m_normalSRV);
			SAFE_RELEASE(m_normalRTV);

			SAFE_RELEASE(m_updateSpectrumCS);
			SAFE_RELEASE(m_quadVS);
			SAFE_RELEASE(m_updateDisplacementPS);
			SAFE_RELEASE(m_genNormalsPS);

			SAFE_RELEASE(m_quadLayout);

			SAFE_RELEASE(m_immutableCB);
			SAFE_RELEASE(m_perFrameCB);
		}

		void thomas::utils::OceanSimulator::Update()
		{
			m_timePassed = Time::GetDeltaTime();

			// ---------------------------- H(0) -> H(t), D(x, t), D(y, t) --------------------------------
			// Compute shader
			ThomasCore::GetDeviceContext()->CSSetShader(m_updateSpectrumCS, NULL, 0);

			// Buffers
			ID3D11ShaderResourceView* cs0_srvs[2] = { m_srvH0, m_srvOmega };
			ThomasCore::GetDeviceContext()->CSSetShaderResources(0, 2, cs0_srvs);

			ID3D11UnorderedAccessView* cs0_uavs[1] = { m_uavHT };
			ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, cs0_uavs, (UINT*)(&cs0_uavs[0]));

			// Consts
			D3D11_MAPPED_SUBRESOURCE mapped_res;
			ThomasCore::GetDeviceContext()->Map(m_perFrameCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_res);

			float* per_frame_data = (float*)mapped_res.pData;
			// g_Time
			per_frame_data[0] = m_timePassed * m_settings.timeScale;
			// g_ChoppyScale
			per_frame_data[1] = m_settings.choppyScale;
			// g_GridLen
			per_frame_data[2] = m_settings.mapDimension / m_settings.patchLength;
			ThomasCore::GetDeviceContext()->Unmap(m_perFrameCB, 0);

			ID3D11Buffer* cs_cbs[2] = { m_immutableCB, m_perFrameCB };
			ThomasCore::GetDeviceContext()->CSSetConstantBuffers(0, 2, cs_cbs);

			// Run the CS
			UINT group_count_x = (m_settings.mapDimension + 16 - 1) / 16; //TODO: Somehting about this block thingy?
			UINT group_count_y = (m_settings.mapDimension + 16 - 1) / 16;
			ThomasCore::GetDeviceContext()->Dispatch(group_count_x, group_count_y, 1);

			// Unbind resources for CS
			cs0_uavs[0] = NULL;
			ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, cs0_uavs, (UINT*)(&cs0_uavs[0]));
			cs0_srvs[0] = NULL;
			cs0_srvs[1] = NULL;
			ThomasCore::GetDeviceContext()->CSSetShaderResources(0, 2, cs0_srvs);

			// ------------------------------------ Perform FFT -------------------------------------------
			FFT512x512Calc(&m_fftPlan, m_uavDxyz, m_srvDxyz, m_srvHT);

			// --------------------------------- Wrap Dx, Dy and Dz ---------------------------------------
			// Push RT
			ID3D11RenderTargetView* old_target;
			ID3D11DepthStencilView* old_depth;
			ThomasCore::GetDeviceContext()->OMGetRenderTargets(1, &old_target, &old_depth);
			D3D11_VIEWPORT old_viewport;
			UINT num_viewport = 1;
			ThomasCore::GetDeviceContext()->RSGetViewports(&num_viewport, &old_viewport);

			D3D11_VIEWPORT new_vp = { 0, 0, (float)m_settings.mapDimension, (float)m_settings.mapDimension, 0.0f, 1.0f };
			ThomasCore::GetDeviceContext()->RSSetViewports(1, &new_vp);

			// Set RT
			ID3D11RenderTargetView* rt_views[1] = { m_displacementRTV };
			ThomasCore::GetDeviceContext()->OMSetRenderTargets(1, rt_views, NULL);

			// VS & PS
			ThomasCore::GetDeviceContext()->VSSetShader(m_quadVS, NULL, 0);
			ThomasCore::GetDeviceContext()->PSSetShader(m_updateDisplacementPS, NULL, 0);

			// Constants
			ID3D11Buffer* ps_cbs[2] = { m_immutableCB, m_perFrameCB };
			ThomasCore::GetDeviceContext()->PSSetConstantBuffers(0, 2, ps_cbs);

			// Buffer resources
			ID3D11ShaderResourceView* ps_srvs[1] = { m_srvDxyz };
			ThomasCore::GetDeviceContext()->PSSetShaderResources(0, 1, ps_srvs);

			// IA setup
			ID3D11Buffer* vbs[1] = { m_pQuadVertexBuffer };
			UINT strides[1] = { sizeof(math::Vector4) };
			UINT offsets[1] = { 0 };
			ThomasCore::GetDeviceContext()->IASetVertexBuffers(0, 1, &vbs[0], &strides[0], &offsets[0]);

			ThomasCore::GetDeviceContext()->IASetInputLayout(m_quadLayout);
			ThomasCore::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			// Perform draw call
			ThomasCore::GetDeviceContext()->Draw(4, 0);

			// Unbind
			ps_srvs[0] = NULL;
			ThomasCore::GetDeviceContext()->PSSetShaderResources(0, 1, ps_srvs);

			// ----------------------------------- Generate Normal ----------------------------------------
			// Set RT
			rt_views[0] = m_normalRTV;
			ThomasCore::GetDeviceContext()->OMSetRenderTargets(1, rt_views, NULL);

			// VS & PS
			ThomasCore::GetDeviceContext()->VSSetShader(m_quadVS, NULL, 0);
			ThomasCore::GetDeviceContext()->PSSetShader(m_genNormalsPS, NULL, 0);

			// Texture resource and sampler
			ps_srvs[0] = m_displacmentSRV;
			ThomasCore::GetDeviceContext()->PSSetShaderResources(0, 1, ps_srvs);

			ID3D11SamplerState* samplers[1] = { m_pointSamplerState };
			ThomasCore::GetDeviceContext()->PSSetSamplers(0, 1, &samplers[0]);

			// Perform draw call
			ThomasCore::GetDeviceContext()->Draw(4, 0);

			// Unbind
			ps_srvs[0] = NULL;
			ThomasCore::GetDeviceContext()->PSSetShaderResources(0, 1, ps_srvs);

			// Pop RT
			ThomasCore::GetDeviceContext()->RSSetViewports(1, &old_viewport);
			ThomasCore::GetDeviceContext()->OMSetRenderTargets(1, &old_target, old_depth);
			SAFE_RELEASE(old_target);
			SAFE_RELEASE(old_depth);

			ThomasCore::GetDeviceContext()->GenerateMips(m_normalSRV);
		}

		ID3D11ShaderResourceView * thomas::utils::OceanSimulator::GetDisplacementMap()
		{
			return m_displacmentSRV;
		}

		ID3D11ShaderResourceView* thomas::utils::OceanSimulator::GetNormalMap()
		{
			return m_normalSRV;
		}

		OceanSimulator::OceanSettings & thomas::utils::OceanSimulator::GetSettings()
		{
			return m_settings;
		}

	}
}

