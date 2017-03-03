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
			s_emitParticlesCS = Shader::CreateComputeShader("EmitParticlesCS", "../res/shaders/emitParticlesCS.hlsl", NULL);
			s_updateParticlesCS = Shader::CreateComputeShader("UpdateParticlesCS", "../res/shaders/updateParticlesCS.hlsl", NULL);

			//CreateBillboardUAVandSRV();


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
			s_cameraBufferStruct.deltaTime = ThomasTime::GetDeltaTime();

			s_matrixBufferStruct.viewProjMatrix = viewProjMatrix;

			thomas::utils::D3d::FillDynamicBufferStruct(s_cameraBuffer, s_cameraBufferStruct);
			thomas::utils::D3d::FillDynamicBufferStruct(s_matrixBuffer, s_matrixBufferStruct);

		}

		void ParticleSystem::SwapUAVsandSRVs(object::component::ParticleEmitterComponent * emitter)
		{
			object::component::ParticleEmitterComponent::D3DData* emitterD3D = emitter->GetD3DData();
			if (emitterD3D->swapUAVandSRV)
			{
				emitterD3D->swapUAVandSRV = false;
			}
			else
			{

				emitterD3D->swapUAVandSRV = true;
			}


			if (emitterD3D->swapUAVandSRV)
			{
				s_activeParticleUAV = emitterD3D->particleUAV1;
				s_activeParticleSRV = emitterD3D->particleSRV2;
			}
			else
			{
				s_activeParticleUAV = emitterD3D->particleUAV2;
				s_activeParticleSRV = emitterD3D->particleSRV1;
			}

		}

		void ParticleSystem::SpawnParticles(object::component::ParticleEmitterComponent * emitter, int amountOfParticles)
		{
			object::component::ParticleEmitterComponent::D3DData* emitterD3D = emitter->GetD3DData();
			ID3D11UnorderedAccessView* nulluav[1] = { NULL };
			s_emitParticlesCS->Bind();
			s_emitParticlesCS->BindBuffer(emitterD3D->particleBuffer, 0);
			s_emitParticlesCS->BindUAV(emitterD3D->particleUAV2, 0);
			s_emitParticlesCS->BindUAV(emitterD3D->particleUAV1, 1);

			ThomasCore::GetDeviceContext()->Dispatch(amountOfParticles, 1, 1);

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
			s_updateParticlesCS->BindUAV(emitter->GetD3DData()->billboardsUAV, 1);
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


			UpdateCameraBuffers(camera->m_gameObject->m_transform, camera->GetViewProjMatrix().Transpose());
			UpdateParticles(emitter);


			FLOAT blendfactor[4] = { 0, 0, 0, 0 };
			ThomasCore::GetDeviceContext()->OMSetBlendState(s_particleBlendState, blendfactor, 0xffffffff);
			//bind Emitter

			emitter->GetShader()->Bind();
			emitter->GetShader()->BindResource(emitter->GetD3DData()->billboardsSRV, 1);
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

		void ParticleSystem::CreateBillboardUAVandSRV(int maxAmountOfParticles, ID3D11Buffer*& buffer, ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv)
		{
			UINT bytewidth = sizeof(BillboardStruct) * maxAmountOfParticles;

			UINT structurebytestride = sizeof(BillboardStruct);
			thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, buffer, uav, srv);

		}



	}
}

