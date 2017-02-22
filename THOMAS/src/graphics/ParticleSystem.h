#pragma once
#include "../utils/Math.h"
#include "../utils/d3d.h"
#include "Shader.h"
#include "Renderer.h"
#include "../object/GameObject.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class EmitterComponent;
		}
	}
	namespace graphics
	{
		static class ParticleSystem
		{
		private:
			static void CreateBillboardUAVandSRV();

			static void CreateParticleUAVsandSRVs(object::component::EmitterComponent* emitter);
			static void CreateInitBuffer(object::component::EmitterComponent* emitter);

			static void InitialDispatch(object::component::EmitterComponent* emitter);

			static void UpdateConstantBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix);
		public:
			ParticleSystem();
			~ParticleSystem();

			
			
			static void Init();
			static void Destroy();
			static void DrawParticles(object::component::Camera * camera);

			struct InitParticleBufferStruct
			{
				math::Vector3 initPosition;
				float initSpread;
				math::Vector3 initDirection;
				float initMaxSpeed;
				float initMinSpeed;
				float initMaxDelay;
				float initMinDelay;
				float initSize;
				float initLifeTime;
				math::Vector3 pad;
			};

			struct ParticleStruct
			{
				math::Vector3 position;
				float spread;
				math::Vector3 direction;
				float speed;
				float delay;
				float size;
				float lifeTimeLeft;
				float pad;
			};

			struct ParticleD3D
			{
				graphics::Shader* m_shader;
				graphics::Texture* m_texture;
				ID3D11UnorderedAccessView* m_particleUAV1;
				ID3D11ShaderResourceView* m_particleSRV1;
				ID3D11Buffer* m_particleBuffer1;
				ID3D11UnorderedAccessView* m_particleUAV2;
				ID3D11ShaderResourceView* m_particleSRV2;
				ID3D11Buffer* m_particleBuffer2;
				bool m_booleanSwapUAVandSRV;

				void SwapUAVsandSRVs(ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv)//ping pong
				{
					if (m_booleanSwapUAVandSRV)
					{
						m_booleanSwapUAVandSRV = false;
					}
					else
					{
						m_booleanSwapUAVandSRV = true;
					}

					if (m_booleanSwapUAVandSRV)
					{
						uav = m_particleUAV1;
						srv = m_particleSRV2;
					}
					else
					{
						uav = m_particleUAV2;
						srv = m_particleSRV1;
					}
				}
			};
			

			static void AddEmitter(object::component::EmitterComponent* emitter);
		private:
			struct BillboardStruct
			{
				math::Vector3 positions[2][3];
				float pad;
				math::Vector2 uvs[2][3];
				float pad2;
				float pad3;
			};
			struct CameraBufferStruct
			{
				math::Vector3 up;
				float deltaTime;
				math::Vector3 right;
				float pad;
			};
			struct MatrixBufferStruct
			{
				math::Matrix viewProjMatrix;
			};
			struct EmitterPosStruct
			{
				math::Vector3 pos;
				float pad;
			};
			
			static CameraBufferStruct s_cameraBufferStruct;
			static MatrixBufferStruct s_matrixBufferStruct;
			static InitParticleBufferStruct s_initParticleBufferStruct;
			static EmitterPosStruct s_emitterPos;
			static ID3D11Buffer* s_cameraBuffer;
			static ID3D11Buffer* s_matrixBuffer;
			static ID3D11Buffer* s_emitterPosBuffer;
			static ID3D11Buffer* s_initParicleBuffer;
			static ID3D11Buffer* s_billboardsBuffer;
			static ID3D11ComputeShader* s_initParticlesCS;
			static ID3D11ComputeShader* s_billboardCS;
			static ID3D11UnorderedAccessView* s_billboardsUAV;
			static ID3D11ShaderResourceView* s_billboardsSRV;

			static ID3D11UnorderedAccessView* s_activeParticleUAV;
			static ID3D11ShaderResourceView* s_activeParticleSRV;

			static ID3D11BlendState* s_particleBlendState;

			static unsigned int s_maxNrOfBillboards;
			static std::vector<object::component::EmitterComponent*> s_emitters;
			static std::vector<object::component::Camera*> s_cameras;
		public:

		};

	
	}
}