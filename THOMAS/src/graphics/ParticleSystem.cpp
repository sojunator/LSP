#include "ParticleSystem.h"
#include "../object/component/EmitterComponent.h"

namespace thomas
{
	namespace graphics
	{

		ParticleSystem::ParticleSystem()
		{
			//CompileComputeShader();
			//m_shader = Shader::GetShaderByName("particleShader");

		}
		ParticleSystem::ParticleSystem(std::string shaderName)
		{
			
			s_shader = Shader::GetShaderByName(shaderName);
			s_nrOfBillboards = 1;
			s_billboards = new Billboard[s_nrOfBillboards];
			CompileComputeShader();
			CreateOutputUAVandSRV();
			
		}

		ParticleSystem::~ParticleSystem()
		{
			delete[] s_billboards;
			
		}
		

		void ParticleSystem::DrawParticles()
		{
			ID3D11UnorderedAccessView* nulluav[1] = { NULL };
			ID3D11ShaderResourceView* nullsrv[1] = { NULL };

			ThomasCore::GetDeviceContext()->CSSetShader(s_billboardCS, NULL, 0);
			//bind uav
			ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &s_billboardsUAV, NULL);

			ThomasCore::GetDeviceContext()->Dispatch(1, 1, 1);
			//unbind uav
			ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, nulluav, NULL);


			s_shader->Bind();


			s_shader->BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			ThomasCore::GetDeviceContext()->IASetInputLayout(NULL);
			ThomasCore::GetDeviceContext()->IASetVertexBuffers(0, 0, nullptr, 0, 0);
			//bind srv
			ThomasCore::GetDeviceContext()->VSSetShaderResources(0, 1, &s_billboardsSRV);
			
			thomas::ThomasCore::GetDeviceContext()->Draw(s_nrOfBillboards * 6, 0);

			//undbind srv
			ThomasCore::GetDeviceContext()->VSSetShaderResources(0, 1, nullsrv);


			s_shader->Unbind();

			return;
		}

		HRESULT ParticleSystem::CreateOutputUAVandSRV()
		{
			D3D11_BUFFER_DESC billboardDesc;
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
			HRESULT hr = S_OK;
			
			billboardDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
			billboardDesc.ByteWidth = sizeof(Billboard) * s_nrOfBillboards;
			billboardDesc.CPUAccessFlags = 0;
			billboardDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			billboardDesc.StructureByteStride = sizeof(Billboard);
			billboardDesc.Usage = D3D11_USAGE_DEFAULT;

			hr = ThomasCore::GetDevice()->CreateBuffer(&billboardDesc, NULL, &s_billboardsBuffer);

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = DXGI_FORMAT_UNKNOWN;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvDesc.Buffer.ElementWidth = s_nrOfBillboards;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = s_nrOfBillboards;
			
			hr = ThomasCore::GetDevice()->CreateShaderResourceView(s_billboardsBuffer, &srvDesc, &s_billboardsSRV);

			ZeroMemory(&uavDesc, sizeof(uavDesc));
			uavDesc.Buffer.FirstElement = 0;
			uavDesc.Buffer.NumElements = s_nrOfBillboards;
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;//D3D11_BUFFER_UAV_FLAG_APPEND;
			uavDesc.Format = DXGI_FORMAT_UNKNOWN;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			hr = ThomasCore::GetDevice()->CreateUnorderedAccessView(s_billboardsBuffer, &uavDesc, &s_billboardsUAV);

			return hr;
		}

		HRESULT ParticleSystem::CompileComputeShader()
		{
			ID3DBlob* shaderBlob = nullptr;
			ID3DBlob* errorBlob = nullptr;

			////////shaderBlob = m_shader->Compile("../res/shaders/billboards.hlsl", "cs_5_0", "main");
			HRESULT hr = D3DCompileFromFile(L"../res/shaders/billboards.hlsl", NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "cs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderBlob, &errorBlob);

			if (FAILED(hr))
			{
				if (errorBlob)
				{
					OutputDebugStringA((char*)errorBlob->GetBufferPointer());
					errorBlob->Release();
				}

				if (shaderBlob)
					shaderBlob->Release();

				LOG("Failed to compile particle shader");
				return hr;
			}
			else
			{
				SAFE_RELEASE(errorBlob);
				hr = ThomasCore::GetDevice()->CreateComputeShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &s_billboardCS);
				SAFE_RELEASE(shaderBlob);
			}

			return hr;
		}


	}
}

