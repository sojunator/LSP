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
		ID3D11Buffer* ParticleSystem::s_billboardsBuffer;

		ID3D11ComputeShader* ParticleSystem::s_billboardCS;
		ID3D11UnorderedAccessView* ParticleSystem::s_billboardsUAV;
		ID3D11ShaderResourceView* ParticleSystem::s_billboardsSRV;

		ID3D11UnorderedAccessView* ParticleSystem::s_activeParticleUAV;
		ID3D11ShaderResourceView* ParticleSystem::s_activeParticleSRV;

		Shader* ParticleSystem::s_shader;
		unsigned int ParticleSystem::s_maxNrOfBillboards;
		std::vector<object::component::Camera*> ParticleSystem::s_cameras;
		std::vector<object::component::EmitterComponent*> ParticleSystem::s_emitters;


		ParticleSystem::ParticleSystem()
		{


		}

		ParticleSystem::~ParticleSystem()
		{

		}

		void ParticleSystem::Init()
		{
			s_shader = Shader::GetShaderByName("particleShader");
			s_maxNrOfBillboards = 10000;
			CompileComputeShader();
			CreateBillboardUAVandSRV();
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
			CreateParticleUAVandSRV(emitter);
			s_emitters.push_back(emitter);
			return;
		}

		void ParticleSystem::DrawParticles(object::component::Camera * camera)
		{
			ID3D11UnorderedAccessView* nulluav[1] = { NULL };
			ID3D11ShaderResourceView* nullsrv[1] = { NULL };

			
			for (object::component::EmitterComponent* emitter : s_emitters)
			{
				UpdateConstantBuffers(camera->m_gameObject->m_transform, camera->GetViewProjMatrix().Transpose());
				ID3D11DeviceContext* deviceContext = ThomasCore::GetDeviceContext();
				deviceContext->CSSetShader(s_billboardCS, NULL, 0);

				emitter->SwapUAVsandSRVs(s_activeParticleUAV, s_activeParticleSRV);

				//bind uavs and srvs
				deviceContext->CSSetUnorderedAccessViews(0, 1, &s_activeParticleUAV, NULL);
				deviceContext->CSSetUnorderedAccessViews(1, 1, &s_billboardsUAV, NULL);
				deviceContext->CSSetShaderResources(0, 1, &s_activeParticleSRV);
				deviceContext->CSSetConstantBuffers(0, 1, &s_cameraBuffer);

				deviceContext->Dispatch(emitter->GetNrOfParticles(), 1, 1);
				//unbind uav
				deviceContext->CSSetUnorderedAccessViews(0, 1, nulluav, NULL);
				deviceContext->CSSetUnorderedAccessViews(1, 1, nulluav, NULL);
				deviceContext->CSGetShaderResources(0, 1, nullsrv);

				//bind srv
				deviceContext->VSSetShaderResources(0, 1, &s_billboardsSRV);
				deviceContext->VSSetConstantBuffers(0, 1, &s_matrixBuffer);

				s_shader->Bind();

				s_shader->BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				deviceContext->IASetInputLayout(NULL);
				deviceContext->IASetVertexBuffers(0, 0, nullptr, 0, 0);


				deviceContext->Draw(emitter->GetNrOfParticles() * 6, 0);

			}
			

			//undbind srv
			ThomasCore::GetDeviceContext()->VSSetShaderResources(0, 1, nullsrv);

			s_shader->Unbind();

			return;
		}

		HRESULT ParticleSystem::CreateBillboardUAVandSRV()
		{
			D3D11_BUFFER_DESC billboardDesc;
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;

			HRESULT hr;

			billboardDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
			billboardDesc.ByteWidth = sizeof(BillboardStruct) * s_maxNrOfBillboards;
			billboardDesc.CPUAccessFlags = 0;
			billboardDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			billboardDesc.StructureByteStride = sizeof(BillboardStruct);
			billboardDesc.Usage = D3D11_USAGE_DEFAULT;

			hr = ThomasCore::GetDevice()->CreateBuffer(&billboardDesc, NULL, &s_billboardsBuffer);
			if (FAILED(hr))
			{
				LOG("Failed to create billboard buffer");
			}

			
			srvDesc.Format = DXGI_FORMAT_UNKNOWN;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = s_maxNrOfBillboards;

			hr = ThomasCore::GetDevice()->CreateShaderResourceView(s_billboardsBuffer, &srvDesc, &s_billboardsSRV);
			if (FAILED(hr))
			{
				LOG("Failed to create billboard srv");
			}

			ZeroMemory(&uavDesc, sizeof(uavDesc));
			uavDesc.Buffer.FirstElement = 0;
			uavDesc.Buffer.NumElements = s_maxNrOfBillboards;
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

		HRESULT ParticleSystem::CreateParticleUAVandSRV(object::component::EmitterComponent* emitter)
		{
			D3D11_BUFFER_DESC particleDesc;
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
			ID3D11UnorderedAccessView*& particleUAV1 = emitter->GetParticleUAV1();
			ID3D11ShaderResourceView*& particleSRV1 = emitter->GetParticleSRV1();
			ID3D11Buffer*& particleBuffer1 = emitter->GetParticleBuffer1();
			ID3D11UnorderedAccessView*& particleUAV2 = emitter->GetParticleUAV2();
			ID3D11ShaderResourceView*& particleSRV2 = emitter->GetParticleSRV2();
			ID3D11Buffer*& particleBuffer2 = emitter->GetParticleBuffer2();

			HRESULT hr;

			particleDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
			particleDesc.ByteWidth = sizeof(ParticleStruct) * emitter->GetNrOfParticles();
			particleDesc.CPUAccessFlags = 0;
			particleDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			particleDesc.StructureByteStride = sizeof(ParticleStruct);
			particleDesc.Usage = D3D11_USAGE_DEFAULT;

			ParticleStruct temp;
			temp.angle = 0;
			temp.direction = math::Vector3(0, 0, 0);
			temp.position = math::Vector3(0, 0, 0);
			temp.speed = 10;

			D3D11_SUBRESOURCE_DATA initData;
			initData.pSysMem = &temp;
			initData.SysMemPitch = 0;
			initData.SysMemSlicePitch = 0;

			hr = ThomasCore::GetDevice()->CreateBuffer(&particleDesc, &initData, &particleBuffer1);
			hr = ThomasCore::GetDevice()->CreateBuffer(&particleDesc, &initData, &particleBuffer2);
			if (FAILED(hr))
			{
				LOG("Failed to create particle buffers");
			}


			srvDesc.Format = DXGI_FORMAT_UNKNOWN;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvDesc.Buffer.FirstElement = 0;
			srvDesc.Buffer.NumElements = emitter->GetNrOfParticles();

			hr = ThomasCore::GetDevice()->CreateShaderResourceView(particleBuffer1, &srvDesc, &particleSRV1);
			hr = ThomasCore::GetDevice()->CreateShaderResourceView(particleBuffer2, &srvDesc, &particleSRV2);
			if (FAILED(hr))
			{
				LOG("Failed to create particle srvs");
			}

			ZeroMemory(&uavDesc, sizeof(uavDesc));
			uavDesc.Buffer.FirstElement = 0;
			uavDesc.Buffer.NumElements = emitter->GetNrOfParticles();
			uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;//D3D11_BUFFER_UAV_FLAG_APPEND;
			uavDesc.Format = DXGI_FORMAT_UNKNOWN;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			hr = ThomasCore::GetDevice()->CreateUnorderedAccessView(particleBuffer1, &uavDesc, &particleUAV1);
			hr = ThomasCore::GetDevice()->CreateUnorderedAccessView(particleBuffer2, &uavDesc, &particleUAV2);
			if (FAILED(hr))
			{
				LOG("Failed to create particle uavs");
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

