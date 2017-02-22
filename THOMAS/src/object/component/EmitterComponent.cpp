#include "EmitterComponent.h"


thomas::object::component::EmitterComponent::EmitterComponent() : Component("EmitterComponent")
{
	
}

void thomas::object::component::EmitterComponent::Init(unsigned int nrOfParticles, bool emitterState, math::Vector3 particleDirection, float minDelay, float maxDelay, 
	float minSpeed, float maxSpeed, math::Vector3 emitterPosition, float particleSpreadFactor, float particleSize, float particleLifeTime, std::string shaderName, std::string texturePath)
{
	m_nrOfParticles = nrOfParticles;//256 * 100 + 254;
	m_isEmitting = emitterState;

	m_particleD3D = new thomas::graphics::ParticleSystem::ParticleD3D();//TODO DELETE
	m_emitterData = new thomas::graphics::ParticleSystem::InitParticleBufferStruct();
	m_emitterData->initDirection = particleDirection;
	m_emitterData->initMaxDelay = maxDelay;
	m_emitterData->initMinDelay = minDelay;
	m_emitterData->initMaxSpeed = maxSpeed;
	m_emitterData->initMinSpeed = minSpeed;
	m_emitterData->initPosition = emitterPosition;
	m_emitterData->initSpread = particleSpreadFactor;
	m_emitterData->initSize = particleSize;
	m_emitterData->initLifeTime = particleLifeTime;

	m_particleD3D->m_shader = graphics::Shader::GetShaderByName(shaderName);
	m_particleD3D->m_texture = graphics::Texture::CreateTexture(thomas::graphics::Texture::SamplerState::WRAP, thomas::graphics::Texture::TextureType::DIFFUSE, texturePath);
	m_particleD3D->m_booleanSwapUAVandSRV = true;

	graphics::ParticleSystem::AddEmitter(this);

	return;
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