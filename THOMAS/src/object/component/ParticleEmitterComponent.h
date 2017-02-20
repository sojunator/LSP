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
			class ParticleEmitterComponent : public Component
			{
			private:
				
			public:
				ParticleEmitterComponent();
				void Emit();
				void Stop();
				unsigned int GetNrOfParticles() const;
				bool IsEmitting() const;

				graphics::ParticleSystem::ParticleD3D* GetParticleD3D() const;
			private:
				
				std::string m_name;
				graphics::ParticleSystem::ParticleD3D* m_particleD3D;
				
				bool m_isEmitting;

				unsigned int m_nrOfParticles;
			};
		}
	}
}
