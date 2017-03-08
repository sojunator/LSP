#pragma once
#include "Thomas.h"
#include "Helper.h"
#include "ShipObject.h"
using namespace thomas;
using namespace object;
class EditorGameObject : public GameObject
{
public:
	EditorGameObject() : GameObject("Editor")
	{

	}

	void Start()
	{
		
		m_transform->SetPosition(0, 20, 0);
		m_particleEmitter = AddComponent<component::ParticleEmitterComponent>();
		m_particleEmitter->StartEmitting();
		m_particleEmitter->AddToDebugMenu();

		m_textureName = m_particleEmitter->GetTexture()->GetName();
		utils::DebugTools::AddString(m_textureName, "Texture path", m_particleEmitter->GetDebugMenuName());
		utils::DebugTools::Bar* bar = utils::DebugTools::GetBar(m_particleEmitter->GetDebugMenuName());
		
		
		TwAddButton(bar->bar, "Browse Textures", Helper::BrowseTextures, NULL, "label='Browse Textures'");
		TwAddButton(bar->bar, "Play/Pause", Helper::PauseToggle, m_particleEmitter, "label='Play/Pause'");
		TwAddButton(bar->bar, "Restart", Helper::Restart, m_particleEmitter, "label='Restart System'");
		TwAddButton(bar->bar, "Export", Helper::SaveSystem, m_particleEmitter, "label='Export system'");
		TwAddButton(bar->bar, "Import", Helper::LoadSystem, m_particleEmitter, "label='Import system'");
		TwAddButton(bar->bar, "Close", Helper::CloseSystem, this, "label='Close System'");
		Helper::s_texturePath = "";
		
		
	}



	void Update()
	{

		if (!Helper::s_texturePath.empty())
		{
			m_textureName = Helper::s_texturePath;
			Helper::s_texturePath = "";
		}

		if (m_particleEmitter->GetTexture()->GetName() != m_textureName)
		{
			m_particleEmitter->SetTexture(m_textureName);
			m_textureName = m_particleEmitter->GetTexture()->GetName();
		}
	}

private:
	std::string m_textureName;
	component::ParticleEmitterComponent* m_particleEmitter;
};