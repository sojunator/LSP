#include "EmitterComponent.h"


thomas::object::component::EmitterComponent::EmitterComponent() : Component("EmitterComponent")
{
	m_nrOfParticles = 256 * 10 + 254;
	m_isEmitting = true;

	m_particleD3D = new thomas::graphics::ParticleSystem::ParticleD3D();//TODO DELETE
	m_emitterData = new thomas::graphics::ParticleSystem::InitParticleBufferStruct();
	m_emitterData->initDirection = math::Vector3(0, 1, 0);
	m_emitterData->initMaxDelay = 5;
	m_emitterData->initMinDelay = 2;
	m_emitterData->initMaxSpeed = 2;
	m_emitterData->initMinSpeed = 1;
	m_emitterData->initPosition = math::Vector3(0,0,0);
	m_emitterData->initSpread = 0.5f;
	m_emitterData->initSize = 1.0f;

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

thomas::graphics::ParticleSystem::InitParticleBufferStruct* thomas::object::component::EmitterComponent::GetInitData() const
{
	return m_emitterData;
}