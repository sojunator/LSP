#include "EmitterComponent.h"


thomas::object::component::EmitterComponent::EmitterComponent() : Component("EmitterComponent")
{
	m_nrOfParticles = 256 * 100 + 254;
	m_isEmitting = false;

	m_particleD3D = new thomas::graphics::ParticleSystem::ParticleD3D();//TODO DELETE
	m_emitterData = new thomas::graphics::ParticleSystem::InitParticleBufferStruct();
	m_emitterData->initDirection = math::Vector3(0, 1, 0);
	m_emitterData->initMaxDelay = 3.8f;
	m_emitterData->initMinDelay = 2.1f;
	m_emitterData->initMaxSpeed = 4;
	m_emitterData->initMinSpeed = 1;
	m_emitterData->initPosition = math::Vector3(9,7,0);
	m_emitterData->initSpread = 0.05f;
	m_emitterData->initSize = 0.2f;
	m_emitterData->initLifeTime = 3;

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