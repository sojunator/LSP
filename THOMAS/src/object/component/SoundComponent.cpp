#include "SoundComponent.h"
#include "../../Sound.h"

thomas::object::component::SoundComponent::SoundComponent(GameObject * gameObject) : Component("SoundObject", gameObject)
{
	m_name == "";
}

bool thomas::object::component::SoundComponent::SetName(std::string name)
{
	if (name[0] == 'm')
	{
		m_name = name;
		return true;
	}
	else if (name[0] == 'f')
	{
		m_name == name;
		return true;
	}
	LOG("'" + name + "' is not an accepted nameformat.");
	return false;
}

std::string thomas::object::component::SoundComponent::GetName()
{
	return m_name;
}

bool thomas::object::component::SoundComponent::Play()
{
	return Sound::Play(m_name);
}

void thomas::object::component::SoundComponent::Pause()
{
	Sound::Pause();
}

void thomas::object::component::SoundComponent::Resume()
{
	Sound::Resume();
}
