#include "ParticleSystem.h"
#include "../object/component/EmitterComponent.h"
#include "../../../DirectXTK-dec2016/Inc/CommonStates.h"
namespace thomas
{
	namespace graphics
	{
		ParticleSystem::CameraBufferStruct ParticleSystem::s_cameraBufferStruct;
		ParticleSystem::MatrixBufferStruct ParticleSystem::s_matrixBufferStruct;
		ParticleSystem::InitParticleBufferStruct ParticleSystem::s_initParticleBufferStruct;
		ParticleSystem::EmitterPosStruct ParticleSystem::s_emitterPos;
		ID3D11Buffer* ParticleSystem::s_cameraBuffer;
		ID3D11Buffer* ParticleSystem::s_matrixBuffer;
		ID3D11Buffer* ParticleSystem::s_emitterPosBuffer;
		ID3D11Buffer* ParticleSystem::s_initParicleBuffer;
		ID3D11Buffer* ParticleSystem::s_billboardsBuffer;

		ID3D11ComputeShader* ParticleSystem::s_initParticlesCS;
		ID3D11ComputeShader* ParticleSystem::s_billboardCS;
		ID3D11UnorderedAccessView* ParticleSystem::s_billboardsUAV;
		ID3D11ShaderResourceView* ParticleSystem::s_billboardsSRV;

		ID3D11UnorderedAccessView* ParticleSystem::s_activeParticleUAV;
		ID3D11ShaderResourceView* ParticleSystem::s_activeParticleSRV;

		ID3D11BlendState* ParticleSystem::s_particleBlendState;

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
			s_maxNrOfBillboards = 100000;
			s_cameraBuffer = nullptr;
			s_matrixBuffer = nullptr;
			ID3DBlob* shaderBlob = thomas::graphics::Shader::Compile("../res/shaders/billboards.hlsl", "cs_5_0", "main");
			HRESULT hr = ThomasCore::GetDevice()->CreateComputeShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &s_billboardCS);
			if (FAILED(hr))
			{
				LOG_HR(hr);
			}
			CreateBillboardUAVandSRV();


			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(blendDesc));

			D3D11_RENDER_TARGET_BLEND_DESC rtbd;
			ZeroMemory(&rtbd, sizeof(rtbd));

			rtbd.BlendEnable = true;
			rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			rtbd.BlendOp = D3D11_BLEND_OP_MIN;
			rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
			rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
			rtbd.BlendOpAlpha = D3D11_BLEND_OP_MIN;
			rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			blendDesc.AlphaToCoverageEnable = false;
			blendDesc.RenderTarget[0] = rtbd;
			

			hr = ThomasCore::GetDevice()->CreateBlendState(&blendDesc, &s_particleBlendState);
			
			return;
		}

		void ParticleSystem::Destroy()
		{
		}

		void ParticleSystem::UpdateConstantBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix)
		{
			s_cameraBufferStruct.right = trans->Right();
			s_cameraBufferStruct.up = trans->Up();
			s_cameraBufferStruct.deltaTime = Time::GetDeltaTime();

			s_matrixBufferStruct.viewProjMatrix = viewProjMatrix;

			if (s_cameraBuffer == nullptr)
			{
				s_cameraBuffer = thomas::utils::D3d::CreateBufferFromStruct(s_cameraBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			}
			else
			{
				ThomasCore::GetDeviceContext()->UpdateSubresource(s_cameraBuffer, 0, NULL, &s_cameraBufferStruct, 0, 0);
			}
			
			if (s_matrixBuffer == nullptr)
			{
				s_matrixBuffer = thomas::utils::D3d::CreateBufferFromStruct(s_matrixBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			}
			else
			{
				ThomasCore::GetDeviceContext()->UpdateSubresource(s_matrixBuffer, 0, NULL, &s_matrixBufferStruct, 0, 0);
			}
			
		}

		void ParticleSystem::AddEmitter(object::component::EmitterComponent* emitter)
		{
			CreateParticleUAVsandSRVs(emitter);
			CreateInitBuffer(emitter);
			ID3DBlob* shaderBlob = thomas::graphics::Shader::Compile("../res/shaders/initParticles.hlsl", "cs_5_0", "main");
			HRESULT hr = ThomasCore::GetDevice()->CreateComputeShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &s_initParticlesCS);
			if (FAILED(hr))
			{
				LOG_HR(hr);
			}
			InitialDispatch(emitter);
			
			struct EmitterPosStruct
			{
				math::Vector3 pos;
				float pad;
			};

			s_emitterPos.pos = emitter->m_gameObject->m_transform->GetPosition();
			s_emitterPosBuffer = thomas::utils::D3d::CreateBufferFromStruct(s_emitterPos, D3D11_BIND_CONSTANT_BUFFER);

			s_emitters.push_back(emitter);
			return;
		}

		void ParticleSystem::DrawParticles(object::component::Camera * camera)
		{
			ID3D11UnorderedAccessView* nulluav[1] = { NULL };
			ID3D11ShaderResourceView* nullsrv[1] = { NULL };

			if (s_emitters.size())
				UpdateConstantBuffers(camera->m_gameObject->m_transform, camera->GetViewProjMatrix().Transpose());

			for (object::component::EmitterComponent* emitter : s_emitters)
			{
				if (emitter->IsEmitting())
				{
					s_emitterPos.pos = emitter->m_gameObject->m_transform->GetPosition();
					ThomasCore::GetDeviceContext()->UpdateSubresource(s_emitterPosBuffer, 0, NULL, &s_emitterPos, 0, 0);
					FLOAT blendfactor[4] = { 0, 0, 0, 0 };
					ThomasCore::GetDeviceContext()->OMSetBlendState(s_particleBlendState, blendfactor, 0xffffffff);

					ID3D11DeviceContext* deviceContext = ThomasCore::GetDeviceContext();
					deviceContext->CSSetShader(s_billboardCS, NULL, 0);

					emitter->GetParticleD3D()->SwapUAVsandSRVs(s_activeParticleUAV, s_activeParticleSRV);

					//bind uavs and srvs
					deviceContext->CSSetUnorderedAccessViews(0, 1, &s_activeParticleUAV, NULL);
					deviceContext->CSSetUnorderedAccessViews(1, 1, &s_billboardsUAV, NULL);
					deviceContext->CSSetShaderResources(0, 1, &s_activeParticleSRV);
					deviceContext->CSSetConstantBuffers(0, 1, &s_cameraBuffer);
					deviceContext->CSSetConstantBuffers(1, 1, &s_emitterPosBuffer);

					deviceContext->Dispatch(emitter->GetNrOfParticles() / 256 + 1, 1, 1);
					//unbind uav
					deviceContext->CSSetUnorderedAccessViews(0, 1, nulluav, NULL);
					deviceContext->CSSetUnorderedAccessViews(1, 1, nulluav, NULL);
					deviceContext->CSSetShaderResources(0, 1, nullsrv);

					//bind srv
					deviceContext->VSSetShaderResources(1, 1, &s_billboardsSRV);
					deviceContext->VSSetConstantBuffers(0, 1, &s_matrixBuffer);

					emitter->GetParticleD3D()->m_shader->Bind();

					emitter->GetParticleD3D()->m_shader->BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
					deviceContext->IASetInputLayout(NULL);
					deviceContext->IASetVertexBuffers(0, 0, nullptr, 0, 0);
					
					emitter->GetParticleD3D()->m_texture->Bind();

					
					deviceContext->Draw(emitter->GetNrOfParticles() * 6, 0);

					ThomasCore::GetDeviceContext()->OMSetBlendState(NULL, NULL, 0xffffffff);

					//undbind srv
					emitter->GetParticleD3D()->m_texture->Unbind();
					deviceContext->VSSetShaderResources(1, 1, nullsrv);
					emitter->GetParticleD3D()->m_shader->Unbind();
				}
			}
			

			return;
		}

		void ParticleSystem::CreateBillboardUAVandSRV()
		{
			UINT bytewidth = sizeof(BillboardStruct) * s_maxNrOfBillboards;
			UINT structurebytestride = sizeof(BillboardStruct);
			thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, s_billboardsBuffer, s_billboardsUAV, s_billboardsSRV);
		}

		void ParticleSystem::CreateParticleUAVsandSRVs(object::component::EmitterComponent* emitter)
		{
			UINT bytewidth = sizeof(ParticleStruct) * emitter->GetNrOfParticles();
			UINT structurebytestride = sizeof(ParticleStruct);
			thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, emitter->GetParticleD3D()->m_particleBuffer1, emitter->GetParticleD3D()->m_particleUAV1, emitter->GetParticleD3D()->m_particleSRV1);
			thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, emitter->GetParticleD3D()->m_particleBuffer2, emitter->GetParticleD3D()->m_particleUAV2, emitter->GetParticleD3D()->m_particleSRV2);
		}

		void ParticleSystem::CreateInitBuffer(object::component::EmitterComponent* emitter)
		{
			s_initParticleBufferStruct = *(emitter->GetInitData());
			s_initParicleBuffer = thomas::utils::D3d::CreateBufferFromStruct(s_initParticleBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			
		}

		void ParticleSystem::InitialDispatch(object::component::EmitterComponent* emitter)
		{
			ID3D11UnorderedAccessView* nulluav[1] = { NULL };
			ThomasCore::GetDeviceContext()->CSSetShader(s_initParticlesCS, 0, NULL);

			ThomasCore::GetDeviceContext()->CSSetConstantBuffers(0, 1, &s_initParicleBuffer);
			
			ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, &emitter->GetParticleD3D()->m_particleUAV2, NULL);
			ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(1, 1, &emitter->GetParticleD3D()->m_particleUAV1, NULL);

			ThomasCore::GetDeviceContext()->Dispatch(emitter->GetNrOfParticles() / 256 + 1, 1, 1);

			ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(0, 1, nulluav, NULL);
			ThomasCore::GetDeviceContext()->CSSetUnorderedAccessViews(1, 1, nulluav, NULL);

			return;
		}


	}
}

