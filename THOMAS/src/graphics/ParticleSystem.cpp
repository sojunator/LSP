#include "ParticleSystem.h"
#include "../object/component/EmitterComponent.h"

namespace thomas
{
	namespace graphics
	{
		ParticleSystem::CameraBufferStruct ParticleSystem::s_cameraBufferStruct;
		ParticleSystem::MatrixBufferStruct ParticleSystem::s_matrixBufferStruct;
		ID3D11Buffer* ParticleSystem::s_matrixBuffer;
		ID3D11Buffer* ParticleSystem::s_cameraBuffer;
		ParticleSystem::Billboard* ParticleSystem::s_billboards;
		ID3D11Buffer* ParticleSystem::s_billboardsBuffer;
		ID3D11ComputeShader* ParticleSystem::s_billboardCS;
		ID3D11UnorderedAccessView* ParticleSystem::s_billboardsUAV;
		ID3D11ShaderResourceView* ParticleSystem::s_billboardsSRV;
		Shader* ParticleSystem::s_shader;
		unsigned int ParticleSystem::s_nrOfBillboards;
		std::vector<object::component::Camera*> ParticleSystem::s_cameras;
		std::vector<object::component::EmitterComponent*> ParticleSystem::s_emitters;


		ParticleSystem::ParticleSystem()
		{


		}

		ParticleSystem::~ParticleSystem()
		{
			delete[] s_billboards;

		}

		void ParticleSystem::Init()
		{
			s_shader = Shader::GetShaderByName("particleShader");
			s_nrOfBillboards = 1;
			s_billboards = new Billboard[s_nrOfBillboards];
			CompileComputeShader();
			CreateOutputUAVandSRV();
			CreateCameraConstantBuffer();
			CreateMatrixConstantBuffer();
			return;
		}

		void ParticleSystem::UpdateConstantBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix)
		{
			s_cameraBufferStruct.forward = trans->Forward();
			s_cameraBufferStruct.right = trans->Right();
			s_cameraBufferStruct.up = trans->Up();
			s_cameraBufferStruct.position = trans->GetPosition();
			ThomasCore::GetDeviceContext()->UpdateSubresource(s_cameraBuffer, 0, NULL, &s_cameraBufferStruct, 0, 0);

			s_matrixBufferStruct.viewProjMatrix = viewProjMatrix;
			ThomasCore::GetDeviceContext()->UpdateSubresource(s_matrixBuffer, 0, NULL, &s_matrixBufferStruct, 0, 0);
		}

		void ParticleSystem::AddEmitter(object::component::EmitterComponent* emitter)
		{
			s_emitters.push_back(emitter);
			return;
		}

		void ParticleSystem::DrawParticles()
		{
			ID3D11UnorderedAccessView* nulluav[1] = { NULL };
			ID3D11ShaderResourceView* nullsrv[1] = { NULL };

			for (object::component::Camera* camera : s_cameras)
			{
				for (object::component::EmitterComponent* emitter : s_emitters)
				{
					UpdateConstantBuffers(camera->m_gameObject->m_transform, camera->GetViewProjMatrix().Transpose());

					ThomasCore::GetDeviceContext()->CSSetShader(s_billboardCS, NULL, 0);
					//bind uav
					ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &s_billboardsUAV, NULL);
					ThomasCore::GetDeviceContext()->CSSetConstantBuffers(0, 1, &s_cameraBuffer);

					ThomasCore::GetDeviceContext()->Dispatch(1, 1, 1);
					//unbind uav
					ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, nulluav, NULL);

					s_shader->Bind();

					s_shader->BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
					ThomasCore::GetDeviceContext()->IASetInputLayout(NULL);
					ThomasCore::GetDeviceContext()->IASetVertexBuffers(0, 0, nullptr, 0, 0);

					//bind srv
					ThomasCore::GetDeviceContext()->VSSetShaderResources(0, 1, &s_billboardsSRV);
					ThomasCore::GetDeviceContext()->VSSetConstantBuffers(0, 1, &s_matrixBuffer);
					//ThomasCore::GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_cameraBuffer);
					

					thomas::ThomasCore::GetDeviceContext()->Draw(emitter->GetNrOfParticles() * 6, 0);

				}
			}

			//undbind srv
			ThomasCore::GetDeviceContext()->VSSetShaderResources(0, 1, nullsrv);

			s_shader->Unbind();

			return;
		}

		HRESULT ParticleSystem::CreateOutputUAVandSRV()
		{
			D3D11_BUFFER_DESC billboardDesc;
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
			HRESULT hr;

			billboardDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
			billboardDesc.ByteWidth = sizeof(Billboard) * s_nrOfBillboards;
			billboardDesc.CPUAccessFlags = 0;
			billboardDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			billboardDesc.StructureByteStride = sizeof(Billboard);
			billboardDesc.Usage = D3D11_USAGE_DEFAULT;

			hr = ThomasCore::GetDevice()->CreateBuffer(&billboardDesc, NULL, &s_billboardsBuffer);
			if (FAILED(hr))
			{
				LOG("Failed to create billboard buffer");
			}

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = DXGI_FORMAT_UNKNOWN;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvDesc.Buffer.ElementWidth = s_nrOfBillboards;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = s_nrOfBillboards;

			hr = ThomasCore::GetDevice()->CreateShaderResourceView(s_billboardsBuffer, &srvDesc, &s_billboardsSRV);
			if (FAILED(hr))
			{
				LOG("Failed to create billboard srv");
			}

			ZeroMemory(&uavDesc, sizeof(uavDesc));
			uavDesc.Buffer.FirstElement = 0;
			uavDesc.Buffer.NumElements = s_nrOfBillboards;
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;//D3D11_BUFFER_UAV_FLAG_APPEND;
			uavDesc.Format = DXGI_FORMAT_UNKNOWN;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			hr = ThomasCore::GetDevice()->CreateUnorderedAccessView(s_billboardsBuffer, &uavDesc, &s_billboardsUAV);
			if (FAILED(hr))
			{
				LOG("Failed to create billboard uav");
			}

			return hr;
		}

		HRESULT ParticleSystem::CreateCameraConstantBuffer()
		{
			HRESULT hr;
			std::vector<object::GameObject*> cameraObjects = object::GameObject::FindGameObjectsWithComponent<object::component::Camera>();

			for (object::GameObject* object : cameraObjects)
				s_cameras.push_back(object->GetComponent<object::component::Camera>());

			object::component::Transform* trans = s_cameras.at(0)->m_gameObject->m_transform;
			s_cameraBufferStruct.forward = trans->Forward();
			s_cameraBufferStruct.right = trans->Right();
			s_cameraBufferStruct.up = trans->Up();
			s_cameraBufferStruct.position = trans->GetPosition();

			D3D11_BUFFER_DESC cbDesc;
			cbDesc.ByteWidth = sizeof(s_cameraBufferStruct);
			cbDesc.Usage = D3D11_USAGE_DEFAULT;
			cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbDesc.CPUAccessFlags = 0;
			cbDesc.MiscFlags = 0;
			cbDesc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA initData;
			initData.pSysMem = &s_cameraBufferStruct;
			initData.SysMemPitch = 0;
			initData.SysMemSlicePitch = 0;

			hr = ThomasCore::GetDevice()->CreateBuffer(&cbDesc, &initData, &s_cameraBuffer);
			if (FAILED(hr))
			{
				LOG("Failed to create camera constant buffer");
			}

			return hr;
		}


		HRESULT ParticleSystem::CreateMatrixConstantBuffer()
		{
			HRESULT hr;

			s_matrixBufferStruct.viewProjMatrix = s_cameras.at(0)->GetViewProjMatrix().Transpose();

			D3D11_BUFFER_DESC cbDesc;
			cbDesc.ByteWidth = sizeof(s_matrixBufferStruct);
			cbDesc.Usage = D3D11_USAGE_DEFAULT;
			cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cbDesc.CPUAccessFlags = 0;
			cbDesc.MiscFlags = 0;
			cbDesc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA initData;
			initData.pSysMem = &s_matrixBufferStruct;
			initData.SysMemPitch = 0;
			initData.SysMemSlicePitch = 0;

			hr = ThomasCore::GetDevice()->CreateBuffer(&cbDesc, &initData, &s_matrixBuffer);
			if (FAILED(hr))
			{
				LOG("Failed to create matrix constant buffer");
			}

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

				LOG("Failed to compile particle computeshader");
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

