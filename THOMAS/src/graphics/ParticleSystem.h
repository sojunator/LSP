#pragma once
#include "../utils/Math.h"
#include "../utils/d3d.h"
#include "Shader.h"
#include "Renderer.h"
#include "../object/GameObject.h"

namespace thomas
{
	namespace graphics
	{
		class EmitterComponent;
		class ParticleSystem
		{
		private:
			HRESULT CompileComputeShader();
			HRESULT CreateOutputUAVandSRV();
		public:
			ParticleSystem();
			ParticleSystem(std::string shaderName);
			~ParticleSystem();

			void DrawParticles();

			struct Particle
			{
				math::Vector3 position;
				int padding;
			};
			struct Billboard
			{
				math::Vector3 positions[2][3];
			};

			
		private:
			Billboard* s_billboards;
			ID3D11Buffer* m_cameraBuffer;
			
			ID3D11Buffer* s_billboardsBuffer;
			ID3D11ComputeShader* s_billboardCS;
			ID3D11UnorderedAccessView* s_billboardsUAV;
			ID3D11ShaderResourceView* s_billboardsSRV;
			Shader* s_shader;
			unsigned int s_nrOfBillboards;
			std::vector<EmitterComponent*> Emitters;

		public:

		};

	
	}
}