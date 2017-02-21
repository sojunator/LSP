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
				bool IsEmitting() const;

				graphics::ParticleSystem::ParticleD3D* GetParticleD3D() const;
				graphics::ParticleSystem::InitParticleBufferStruct* GetInitData() const;
			private:
				
				std::string m_name;
				graphics::ParticleSystem::ParticleD3D* m_particleD3D;
				graphics::ParticleSystem::InitParticleBufferStruct* m_emitterData;
				
				bool m_isEmitting;

				unsigned int m_nrOfParticles;
			};
		}
	}
}
