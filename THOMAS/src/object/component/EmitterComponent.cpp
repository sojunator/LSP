#include "EmitterComponent.h"


thomas::object::component::EmitterComponent::EmitterComponent() : Component("EmitterComponent")
{
	m_nrOfParticles = 80;
	m_isEmitting = false;
	m_booleanSwapUAVandSRV = true;
	graphics::ParticleSystem::AddEmitter(this);
}

void thomas::object::component::EmitterComponent::Emit()
{
	m_isEmitting = true;



}

void thomas::object::component::EmitterComponent::Stop()
{
	m_isEmitting = false;
}

unsigned int thomas::object::component::EmitterComponent::GetNrOfParticles() const
{
	return m_nrOfParticles;
}

void thomas::object::component::EmitterComponent::SwapUAVsandSRVs(ID3D11UnorderedAccessView*& uav, ID3D11ShaderResourceView*& srv)
{
	if (m_booleanSwapUAVandSRV)
	{
		m_booleanSwapUAVandSRV = false;
	}
	else
	{
		m_booleanSwapUAVandSRV = true;
	}

	if (m_booleanSwapUAVandSRV)
	{
		uav = m_particleUAV1;
		srv = m_particleSRV2;
	}
	else
	{
		uav = m_particleUAV2;
		srv = m_particleSRV1;
	}
}
//TODO PEKAR REFERENS 
ID3D11UnorderedAccessView* thomas::object::component::EmitterComponent::GetParticleUAV1() const
{
	return m_particleUAV1;
}
ID3D11ShaderResourceView* thomas::object::component::EmitterComponent::GetParticleSRV1() const
{
	return m_particleSRV1;
}
ID3D11UnorderedAccessView* thomas::object::component::EmitterComponent::GetParticleUAV2() const
{
	return m_particleUAV2;
}
ID3D11ShaderResourceView* thomas::object::component::EmitterComponent::GetParticleSRV2() const
{
	return m_particleSRV2;
}
ID3D11Buffer* thomas::object::component::EmitterComponent::GetParticleBuffer1() const
{
	return m_particleBuffer1;
}
ID3D11Buffer* thomas::object::component::EmitterComponent::GetParticleBuffer2() const
{
	return m_particleBuffer2;
}