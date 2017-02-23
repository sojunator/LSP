#pragma once
#include "../utils/Math.h"
#include "../utils/d3d.h"
#include "Shader.h"
#include "Renderer.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class EmitterComponent;
			class Transform;
		}
	}
	namespace graphics
	{
		static class ParticleSystem
		{
		private:
			static void CreateBillboardUAVandSRV();

			static void UpdateConstantBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix, math::Vector3 emitterPos);
		public:
			ParticleSystem();
			~ParticleSystem();

			
			
			static void Init();
			static void Destroy();
			static void DrawParticles(object::component::Camera * camera, object::component::EmitterComponent* emitter);

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
			static EmitterPosStruct s_emitterPos;
			static ID3D11Buffer* s_cameraBuffer;
			static ID3D11Buffer* s_matrixBuffer;
			static ID3D11Buffer* s_emitterPosBuffer;
			
			static ID3D11Buffer* s_billboardsBuffer;
			
			static ID3D11ComputeShader* s_billboardCS;
			static ID3D11UnorderedAccessView* s_billboardsUAV;
			static ID3D11ShaderResourceView* s_billboardsSRV;

			static ID3D11UnorderedAccessView* s_activeParticleUAV;
			static ID3D11ShaderResourceView* s_activeParticleSRV;

			static ID3D11BlendState* s_particleBlendState;

			static unsigned int s_maxNrOfBillboards;
		public:

		};

	
	}
}