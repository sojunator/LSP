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

		ParticleSystem::BlendStates ParticleSystem::s_blendStates;
		ID3D11DepthStencilState* ParticleSystem::s_depthStencilState;

		unsigned int ParticleSystem::s_maxNumberOfBillboardsSupported;


		ParticleSystem::ParticleSystem()
		{


		}

		ParticleSystem::~ParticleSystem()
		{
			s_depthStencilState->Release();
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

			D3D11_RENDER_TARGET_BLEND_DESC blendState;
			ZeroMemory(&blendState, sizeof(blendState));

			//Additive

			blendState.BlendEnable = true;
			blendState.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendState.DestBlend = D3D11_BLEND_ONE;
			blendState.BlendOp = D3D11_BLEND_OP_ADD;
			blendState.SrcBlendAlpha = D3D11_BLEND_ONE;
			blendState.DestBlendAlpha = D3D11_BLEND_ZERO;
			blendState.BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendState.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			blendDesc.RenderTarget[0] = blendState;

			HRESULT hr = ThomasCore::GetDevice()->CreateBlendState(&blendDesc, &s_blendStates.additive);

			//alpha blend
			blendState.BlendEnable = true;
			blendState.SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendState.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendState.BlendOp = D3D11_BLEND_OP_ADD;
			blendState.SrcBlendAlpha = D3D11_BLEND_ONE;
			blendState.DestBlendAlpha = D3D11_BLEND_ZERO;
			blendState.BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendState.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
			blendDesc.RenderTarget[0] = blendState;

			hr = ThomasCore::GetDevice()->CreateBlendState(&blendDesc, &s_blendStates.alphaBlend);


			D3D11_DEPTH_STENCIL_DESC mirrorDesc;
			mirrorDesc.DepthEnable = true;
			mirrorDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
			mirrorDesc.DepthFunc = D3D11_COMPARISON_LESS;
			mirrorDesc.StencilEnable = false;
			mirrorDesc.StencilReadMask = 0xff;
			mirrorDesc.StencilWriteMask = 0xff;
			mirrorDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			mirrorDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
			mirrorDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
			mirrorDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			ThomasCore::GetDevice()->CreateDepthStencilState(&mirrorDesc, &s_depthStencilState);


			s_cameraBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(s_cameraBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			s_matrixBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(s_matrixBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			return;
		}

		void ParticleSystem::Destroy()
		{
		}

		void ParticleSystem::UpdateCameraBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix, bool paused)
		{
			s_cameraBufferStruct.right = trans->Right();
			s_cameraBufferStruct.up = trans->Up();
			if (paused)
			{
				s_cameraBufferStruct.deltaTime = 0;
			}
			else
			{
				s_cameraBufferStruct.deltaTime = ThomasTime::GetDeltaTime();
			}


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


			UpdateCameraBuffers(camera->m_gameObject->m_transform, camera->GetViewProjMatrix().Transpose(), emitter->IsPaused());
			UpdateParticles(emitter);


			FLOAT blendfactor[4] = { 0, 0, 0, 0 };

			switch (emitter->GetBlendState())
			{
			case object::component::ParticleEmitterComponent::BlendStates::ADDITIVE:
				ThomasCore::GetDeviceContext()->OMSetBlendState(s_blendStates.additive, blendfactor, 0xffffffff);
				break;
			case object::component::ParticleEmitterComponent::BlendStates::ALPHA_BLEND:
				ThomasCore::GetDeviceContext()->OMSetBlendState(s_blendStates.alphaBlend, blendfactor, 0xffffffff);
				break;
			default:
				ThomasCore::GetDeviceContext()->OMSetBlendState(s_blendStates.additive, blendfactor, 0xffffffff);
				break;
			}

			//bind Emitter

			emitter->GetShader()->Bind();
			emitter->GetShader()->BindResource(emitter->GetD3DData()->billboardsSRV, 1);
			emitter->GetShader()->BindBuffer(s_matrixBuffer, 0);
			ThomasCore::GetDeviceContext()->IASetInputLayout(NULL);
			emitter->GetShader()->BindVertexBuffer(NULL, 0, 0);

			emitter->GetTexture()->Bind();

			emitter->GetShader()->BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			ThomasCore::GetDeviceContext()->Draw(emitter->GetNrOfMaxParticles() * 6, 0);

			ThomasCore::GetDeviceContext()->OMSetBlendState(NULL, NULL, 0xffffffff);

			//undbind Emitter
			emitter->GetTexture()->Unbind();
			emitter->GetShader()->BindResource(NULL, 1);
			emitter->GetShader()->BindBuffer(NULL, 0);
			emitter->GetShader()->Unbind();
		}

		ID3D11DepthStencilState * ParticleSystem::GetDepthStencilState()
		{
			return s_depthStencilState;
		}

		void ParticleSystem::CreateBillboardUAVandSRV(int maxAmountOfParticles, ID3D11Buffer*& buffer, ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv)
		{
			UINT bytewidth = sizeof(BillboardStruct) * maxAmountOfParticles;

			UINT structurebytestride = sizeof(BillboardStruct);
			thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, buffer, uav, srv);

		}



	}
}

