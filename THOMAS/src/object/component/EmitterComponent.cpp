#include "EmitterComponent.h"

void thomas::object::component::EmitterComponent::Emit()
{
	m_isEmitting = true;



}

void thomas::object::component::EmitterComponent::Stop()
{
	m_isEmitting = false;
}
