#include "ParticleSystem.h"

namespace thomas
{
	namespace graphics
	{
		ParticleSystem::CameraBufferStruct ParticleSystem::s_cameraBufferStruct;
		ParticleSystem::MatrixBufferStruct ParticleSystem::s_matrixBufferStruct;
		ID3D11Buffer* ParticleSystem::s_cameraBuffer;
		ID3D11Buffer* ParticleSystem::s_matrixBuffer;

		ID3D11Buffer* ParticleSystem::s_billboardsBuffer;

		Shader* ParticleSystem::s_updateParticlesCS;
		Shader* ParticleSystem::s_emitParticlesCS;
		ID3D11UnorderedAccessView* ParticleSystem::s_billboardsUAV;
		ID3D11ShaderResourceView* ParticleSystem::s_billboardsSRV;

		ID3D11UnorderedAccessView* ParticleSystem::s_activeParticleUAV; //ping
		ID3D11ShaderResourceView* ParticleSystem::s_activeParticleSRV; //pong

		ID3D11BlendState* ParticleSystem::s_particleBlendState;

		unsigned int ParticleSystem::s_maxNumberOfBillboardsSupported;


		ParticleSystem::ParticleSystem()
		{


		}

		ParticleSystem::~ParticleSystem()
		{

		}

		void ParticleSystem::Init()
		{
			s_maxNumberOfBillboardsSupported = 1000000;
			s_cameraBuffer = nullptr;
			s_matrixBuffer = nullptr;
			s_emitParticlesCS = Shader::CreateComputeShader("EmitParticlesCS","../res/shaders/initParticles.hlsl", NULL);
			s_updateParticlesCS = Shader::CreateComputeShader("UpdateParticlesCS", "../res/shaders/billboards.hlsl", NULL);

			CreateBillboardUAVandSRV();


			D3D11_BLEND_DESC blendDesc;
			ZeroMemory(&blendDesc, sizeof(blendDesc));

			D3D11_RENDER_TARGET_BLEND_DESC rtbd;
			ZeroMemory(&rtbd, sizeof(rtbd));

			rtbd.BlendEnable = true;
			rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			rtbd.BlendOp = D3D11_BLEND_OP_ADD;
			rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
			rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
			rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
			rtbd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

			blendDesc.AlphaToCoverageEnable = true;
			blendDesc.RenderTarget[0] = rtbd;
			

			HRESULT hr = ThomasCore::GetDevice()->CreateBlendState(&blendDesc, &s_particleBlendState);
			

			s_cameraBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(s_cameraBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			s_matrixBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(s_matrixBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			return;
		}

		void ParticleSystem::Destroy()
		{
		}

		void ParticleSystem::UpdateCameraBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix)
		{
			s_cameraBufferStruct.right = trans->Right();
			s_cameraBufferStruct.up = trans->Up();
			s_cameraBufferStruct.deltaTime = Time::GetDeltaTime();

			s_matrixBufferStruct.viewProjMatrix = viewProjMatrix;

			thomas::utils::D3d::FillDynamicBufferStruct(s_cameraBuffer, s_cameraBufferStruct);
			thomas::utils::D3d::FillDynamicBufferStruct(s_matrixBuffer, s_matrixBufferStruct);
			
		}

		void ParticleSystem::SwapUAVsandSRVs(object::component::ParticleEmitterComponent * emitter)
		{
			object::component::ParticleEmitterComponent::D3DData* emitterD3D = emitter->GetD3DData();
			if (emitterD3D->m_booleanSwapUAVandSRV)
			{
				emitterD3D->m_booleanSwapUAVandSRV = false;
			}
			else
			{

				emitterD3D->m_booleanSwapUAVandSRV = true;
			}
			

			if (emitterD3D->m_booleanSwapUAVandSRV)
			{
				s_activeParticleUAV = emitterD3D->m_particleUAV1;
				s_activeParticleSRV = emitterD3D->m_particleSRV2;
			}
			else
			{
				s_activeParticleUAV = emitterD3D->m_particleUAV2;
				s_activeParticleSRV = emitterD3D->m_particleSRV1;
			}
		
		}

		void ParticleSystem::SpawnParticles(object::component::ParticleEmitterComponent * emitter, int amountOfParticles)
		{
			ID3D11UnorderedAccessView* nulluav[1] = { NULL };
			s_emitParticlesCS->Bind();
			s_emitParticlesCS->BindBuffer(emitter->m_particleBuffer, 0);
			s_emitParticlesCS->BindUAV(m_particleUAV2, 0);
			s_emitParticlesCS->BindUAV(m_particleUAV1, 1);

			ThomasCore::GetDeviceContext()->Dispatch(GetNrOfParticles() / 256 + 1, 1, 1);

			s_emitParticlesCS->BindUAV(NULL, 0);
			s_emitParticlesCS->BindUAV(NULL, 0);
			s_emitParticlesCS->BindBuffer(NULL, 0);
			s_emitParticlesCS->Unbind();
		}

		void ParticleSystem::UpdateParticles(object::component::ParticleEmitterComponent * emitter)
		{
									
				SwapUAVsandSRVs(emitter);

				//bind CS
				s_updateParticlesCS->Bind();
				s_updateParticlesCS->BindUAV(s_activeParticleUAV, 0);
				s_updateParticlesCS->BindUAV(s_billboardsUAV, 1);
				s_updateParticlesCS->BindResource(s_activeParticleSRV, 0);
				s_updateParticlesCS->BindBuffer(s_cameraBuffer, 0);

				ThomasCore::GetDeviceContext()->Dispatch(emitter->GetNrOfMaxParticles() / 256 + 1, 1, 1);
				//unbind CS
				s_updateParticlesCS->BindUAV(NULL, 0);
				s_updateParticlesCS->BindUAV(NULL, 1);
				s_updateParticlesCS->BindResource(NULL, 0);
				s_updateParticlesCS->Unbind();

			
			
		}

		void ParticleSystem::DrawParticles(object::component::Camera * camera, object::component::ParticleEmitterComponent* emitter)
		{

			if (emitter->IsEmitting())
			{
				UpdateCameraBuffers(camera->m_gameObject->m_transform, camera->GetViewProjMatrix().Transpose());
				UpdateParticles(emitter);


				FLOAT blendfactor[4] = { 0, 0, 0, 0 };
				ThomasCore::GetDeviceContext()->OMSetBlendState(s_particleBlendState, blendfactor, 0xffffffff);
				//bind Emitter

				emitter->GetShader()->Bind();
				emitter->GetShader()->BindResource(s_billboardsSRV,1);
				emitter->GetShader()->BindBuffer(s_matrixBuffer, 0);
				ThomasCore::GetDeviceContext()->IASetInputLayout(NULL);
				emitter->GetShader()->BindVertexBuffer(NULL, 0, 0);
					
				emitter->GetTexture()->Bind();
	
				ThomasCore::GetDeviceContext()->Draw(emitter->GetNrOfMaxParticles() * 6, 0);

				ThomasCore::GetDeviceContext()->OMSetBlendState(NULL, NULL, 0xffffffff);

				//undbind Emitter
				emitter->GetTexture()->Unbind();
				emitter->GetShader()->BindResource(NULL, 1);
				emitter->GetShader()->BindBuffer(NULL, 0);
				emitter->GetShader()->Unbind();
			}
			
			

			return;
		}

		void ParticleSystem::CreateBillboardUAVandSRV()
		{
			UINT bytewidth = sizeof(BillboardStruct) * s_maxNumberOfBillboardsSupported;
			UINT structurebytestride = sizeof(BillboardStruct);
			thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, s_billboardsBuffer, s_billboardsUAV, s_billboardsSRV);
		}

		
	
	}
}

