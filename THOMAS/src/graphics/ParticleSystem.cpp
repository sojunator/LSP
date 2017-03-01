#include "ParticleSystem.h"

namespace thomas
{
	namespace graphics
	{
		ParticleSystem::CameraBufferStruct ParticleSystem::s_cameraBufferStruct;
		ParticleSystem::MatrixBufferStruct ParticleSystem::s_matrixBufferStruct;
		ParticleSystem::EmitterPosStruct ParticleSystem::s_emitterPos;
		ID3D11Buffer* ParticleSystem::s_cameraBuffer;
		ID3D11Buffer* ParticleSystem::s_matrixBuffer;
		ID3D11Buffer* ParticleSystem::s_emitterPosBuffer;

		ID3D11Buffer* ParticleSystem::s_billboardsBuffer;

		Shader* ParticleSystem::s_billboardCS;
		Shader* ParticleSystem::s_initParticleCS;
		ID3D11UnorderedAccessView* ParticleSystem::s_billboardsUAV;
		ID3D11ShaderResourceView* ParticleSystem::s_billboardsSRV;

		ID3D11UnorderedAccessView* ParticleSystem::s_activeParticleUAV;
		ID3D11ShaderResourceView* ParticleSystem::s_activeParticleSRV;

		ID3D11BlendState* ParticleSystem::s_particleBlendState;

		unsigned int ParticleSystem::s_maxNrOfBillboards;


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
			s_emitterPosBuffer = nullptr;
			s_initParticleCS = Shader::CreateComputeShader("InitParticleCS","../res/shaders/initParticles.hlsl", NULL);
			s_billboardCS = Shader::CreateComputeShader("ParticleCS", "../res/shaders/billboards.hlsl", NULL);

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
			
			return;
		}

		void ParticleSystem::Destroy()
		{
		}

		void ParticleSystem::UpdateConstantBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix, math::Vector3 emitterPos)
		{
			s_cameraBufferStruct.right = trans->Right();
			s_cameraBufferStruct.up = trans->Up();
			s_cameraBufferStruct.deltaTime = Time::GetDeltaTime();

			s_matrixBufferStruct.viewProjMatrix = viewProjMatrix;

			s_emitterPos.pos = emitterPos;

			if (s_cameraBuffer == nullptr)
			{
				s_cameraBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(s_cameraBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			}
			else
			{
				thomas::utils::D3d::FillDynamicBufferStruct(s_cameraBuffer, s_cameraBufferStruct);
			}
			
			if (s_matrixBuffer == nullptr)
			{
				s_matrixBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(s_matrixBufferStruct, D3D11_BIND_CONSTANT_BUFFER);
			}
			else
			{
				thomas::utils::D3d::FillDynamicBufferStruct(s_matrixBuffer, s_matrixBufferStruct);
			}
			if (s_emitterPosBuffer == nullptr)
			{
				s_emitterPosBuffer = thomas::utils::D3d::CreateDynamicBufferFromStruct(s_emitterPos, D3D11_BIND_CONSTANT_BUFFER);
			}
			else
			{
				thomas::utils::D3d::FillDynamicBufferStruct(s_emitterPosBuffer, s_emitterPos);
			}
		}

		void ParticleSystem::DrawParticles(object::component::Camera * camera, object::component::ParticleEmitterComponent* emitter)
		{
			ID3D11UnorderedAccessView* nulluav[1] = { NULL };
			ID3D11ShaderResourceView* nullsrv[1] = { NULL };

			if (emitter->IsEmitting())
			{
				UpdateConstantBuffers(camera->m_gameObject->m_transform, camera->GetViewProjMatrix().Transpose(), emitter->m_gameObject->m_transform->GetPosition());
					
				FLOAT blendfactor[4] = { 0, 0, 0, 0 };
				ThomasCore::GetDeviceContext()->OMSetBlendState(s_particleBlendState, blendfactor, 0xffffffff);

						

				emitter->SwapUAVsandSRVs(s_activeParticleUAV, s_activeParticleSRV);

				//bind CS
				s_billboardCS->Bind();
				s_billboardCS->BindUAV(s_activeParticleUAV, 0);
				s_billboardCS->BindUAV(s_billboardsUAV, 1);
				s_billboardCS->BindResource(s_activeParticleSRV, 0);
				s_billboardCS->BindBuffer(s_cameraBuffer, 0);
				s_billboardCS->BindBuffer(s_emitterPosBuffer, 1);

				ThomasCore::GetDeviceContext()->Dispatch(emitter->GetNrOfParticles() / 256 + 1, 1, 1);
				//unbind CS
				s_billboardCS->BindUAV(NULL, 0);
				s_billboardCS->BindUAV(NULL, 1);
				s_billboardCS->BindResource(NULL, 0);
				s_billboardCS->Unbind();
				//bind Emitter

				emitter->GetShader()->Bind();
				emitter->GetShader()->BindResource(s_billboardsSRV,1);
				emitter->GetShader()->BindBuffer(s_matrixBuffer, 0);
				ThomasCore::GetDeviceContext()->IASetInputLayout(NULL);
				emitter->GetShader()->BindVertexBuffer(NULL, 0, 0);
					
				emitter->GetTexture()->Bind();
	
				ThomasCore::GetDeviceContext()->Draw(emitter->GetNrOfParticles() * 6, 0);

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
			UINT bytewidth = sizeof(BillboardStruct) * s_maxNrOfBillboards;
			UINT structurebytestride = sizeof(BillboardStruct);
			thomas::utils::D3d::CreateBufferAndUAV(NULL, bytewidth, structurebytestride, s_billboardsBuffer, s_billboardsUAV, s_billboardsSRV);
		}

		
	
	}
}

