#include "EmitterComponent.h"


thomas::object::component::EmitterComponent::EmitterComponent() : Component("EmitterComponent")
{
	m_nrOfParticles = 5832;
	m_isEmitting = true;

	m_particleD3D = new thomas::graphics::ParticleSystem::ParticleD3D();

	m_particleD3D->m_shader = graphics::Shader::GetShaderByName("particleShader");
	m_particleD3D->m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, "../res/textures/smokeParticleDank.png");
	m_particleD3D->m_booleanSwapUAVandSRV = true;

	graphics::ParticleSystem::AddEmitter(this);
}

void thomas::object::component::EmitterComponent::Emit()
{
	m_isEmitting = true;

}

bool thomas::object::component::EmitterComponent::IsEmitting() const
{
	return m_isEmitting;
}


void thomas::object::component::EmitterComponent::Stop()
{
	m_isEmitting = false;
}

unsigned int thomas::object::component::EmitterComponent::GetNrOfParticles() const
{
	return m_nrOfParticles;
}



thomas::graphics::ParticleSystem::ParticleD3D* thomas::object::component::EmitterComponent::GetParticleD3D() const
{
	return m_particleD3D;
}