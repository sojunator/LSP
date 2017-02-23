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
				void Init(unsigned int nrOfParticles, bool emitterState, math::Vector3 particleDirection, float minDelay, float maxDelay, float minSpeed, float maxSpeed, 
					math::Vector3 emitterPosition, float particleSpreadFactor, float particleSize, float particleLifeTime, std::string shaderName, std::string texturePath);
				void Destroy();
				void Update(unsigned int nrOfParticles, bool emitterState, math::Vector3 particleDirection, float minDelay, float maxDelay, float minSpeed, float maxSpeed,
					math::Vector3 emitterPosition, float particleSpreadFactor, float particleSize, float particleLifeTime, std::string shaderName, std::string texturePath);
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
