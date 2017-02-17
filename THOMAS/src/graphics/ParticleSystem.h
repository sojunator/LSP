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
			static HRESULT CompileComputeShader();
			static HRESULT CreateBillboardUAVandSRV();
			static HRESULT CreateCameraConstantBuffer();
			static HRESULT CreateMatrixConstantBuffer();
			static HRESULT CreateParticleUAVandSRV(object::component::EmitterComponent* emitter);

			static void UpdateConstantBuffers(object::component::Transform* trans, math::Matrix viewProjMatrix);
		public:
			ParticleSystem();
			~ParticleSystem();
			
			static void Init();
			static void DrawParticles(object::component::Camera * camera);

			struct ParticleStruct
			{
				math::Vector3 position;
				float speed;
				math::Vector3 direction;
				float angle;
			};
			

			static void AddEmitter(object::component::EmitterComponent* emitter);
		private:
			struct BillboardStruct
			{
				math::Vector3 positions[2][3];
			};
			struct CameraBufferStruct
			{
				math::Vector3 forward;
				float pad;
				math::Vector3 up;
				float pad2;
				math::Vector3 right;
				float pad3;
				math::Vector3 position;
				float pad4;
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
			static ID3D11ComputeShader* s_billboardCS;
			static ID3D11UnorderedAccessView* s_billboardsUAV;
			static ID3D11ShaderResourceView* s_billboardsSRV;

			static ID3D11UnorderedAccessView* s_activeParticleUAV;
			static ID3D11ShaderResourceView* s_activeParticleSRV;

			static Shader* s_shader;
			static unsigned int s_maxNrOfBillboards;
			static std::vector<object::component::EmitterComponent*> s_emitters;
			static std::vector<object::component::Camera*> s_cameras;

		public:

		};

	
	}
}