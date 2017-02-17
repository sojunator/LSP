#include "EmitterComponent.h"


thomas::object::component::EmitterComponent::EmitterComponent() : Component("EmitterComponent")
{
	m_nrOfParticles = 50;
	m_isEmitting = false;
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
