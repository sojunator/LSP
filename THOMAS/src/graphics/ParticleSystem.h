#pragma once
#include "../utils/Math.h"
#include "../utils/d3d.h"
#include "Shader.h"
#include "Renderer.h"
#include "../object/component/ParticleEmitterComponent.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class ParticleEmitterComponent;
			class Transform;
		}
	}
	namespace graphics
	{
		static class ParticleSystem
		{
		private:
			

			static void UpdateCameraBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix);
			static void SwapUAVsandSRVs(object::component::ParticleEmitterComponent * emitter);//ping pong
			
		public:
			ParticleSystem();
			~ParticleSystem();

			static void CreateBillboardUAVandSRV(int maxAmountOfParticles, ID3D11Buffer*& buffer, ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv);
			static void Init();
			static void Destroy();
			static void SpawnParticles(object::component::ParticleEmitterComponent* emitter, int amountOfParticles);
			static void UpdateParticles(object::component::ParticleEmitterComponent* emitter);
			static void DrawParticles(object::component::Camera * camera, object::component::ParticleEmitterComponent* emitter);

		private:
			struct BillboardStruct
			{
				math::Vector3 positions[2][3];
				math::Vector2 pad2;
				math::Vector2 uvs[2][3];
				math::Vector4 colorFactor;
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
			
			static CameraBufferStruct s_cameraBufferStruct;
			static MatrixBufferStruct s_matrixBufferStruct;
			static ID3D11Buffer* s_cameraBuffer;
			static ID3D11Buffer* s_matrixBuffer;
			
			static ID3D11Buffer* s_billboardsBuffer;
			
			static Shader* s_updateParticlesCS;
			static Shader* s_emitParticlesCS;
			static ID3D11UnorderedAccessView* s_billboardsUAV;
			static ID3D11ShaderResourceView* s_billboardsSRV;

			static ID3D11UnorderedAccessView* s_activeParticleUAV;
			static ID3D11ShaderResourceView* s_activeParticleSRV;

			static ID3D11BlendState* s_particleBlendState;

			static unsigned int s_maxNumberOfBillboardsSupported;
		public:

		};

	
	}
}