#pragma once
#include "Component.h"
#include "..\..\utils\math.h"
#include "..\..\graphics\Texture.h"
#include "..\..\graphics\Shader.h"
#include "..\..\graphics\ParticleSystem.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			class EmitterComponent : public Component
			{
			private:
				
			public:
				EmitterComponent();
				void Emit();
				void Stop();
				unsigned int GetNrOfParticles() const;

				void SwapUAVsandSRVs(ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv);

				ID3D11UnorderedAccessView*& GetParticleUAV1();
				ID3D11ShaderResourceView*& GetParticleSRV1();
				ID3D11Buffer*& GetParticleBuffer1();
				ID3D11UnorderedAccessView*& GetParticleUAV2();
				ID3D11ShaderResourceView*& GetParticleSRV2();
				ID3D11Buffer*& GetParticleBuffer2();
			private:
				graphics::Texture* m_texture;
				std::string m_name;
				
				ID3D11UnorderedAccessView* m_particleUAV1;
				ID3D11ShaderResourceView* m_particleSRV1;
				ID3D11Buffer* m_particleBuffer1;
				ID3D11UnorderedAccessView* m_particleUAV2;
				ID3D11ShaderResourceView* m_particleSRV2;
				ID3D11Buffer* m_particleBuffer2;
				bool m_booleanSwapUAVandSRV;


				bool m_isEmitting;

				//graphics::ParticleSystem::ParticleStruct m_particle;

				unsigned int m_nrOfParticles;
			};
		}
	}
}
