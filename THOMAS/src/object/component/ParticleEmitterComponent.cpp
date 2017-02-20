#include "ParticleEmitterComponent.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			ParticleEmitterComponent::ParticleEmitterComponent() : Component("ParticleEmitterComponent")
			{
				m_nrOfParticles = 5832;
				m_isEmitting = true;

				m_particleD3D = new thomas::graphics::ParticleSystem::ParticleD3D();

				m_particleD3D->m_shader = graphics::Shader::GetShaderByName("particleShader");
				m_particleD3D->m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, "../res/textures/smokeParticleDank.png");
				m_particleD3D->m_booleanSwapUAVandSRV = true;

				graphics::ParticleSystem::AddEmitter(this);
			}

			void ParticleEmitterComponent::Emit()
			{
				m_isEmitting = true;

			}

			bool ParticleEmitterComponent::IsEmitting() const
			{
				return m_isEmitting;
			}


			void ParticleEmitterComponent::Stop()
			{
				m_isEmitting = false;
			}

			unsigned int ParticleEmitterComponent::GetNrOfParticles() const
			{
				return m_nrOfParticles;
			}



			graphics::ParticleSystem::ParticleD3D* ParticleEmitterComponent::GetParticleD3D() const
			{
				return m_particleD3D;
			}
		}
	}
}

