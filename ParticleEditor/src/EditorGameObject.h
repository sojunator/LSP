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

		m_tempTextureName = m_particleEmitter->GetTexture()->GetName();
		m_textureName = m_tempTextureName;
		m_temp2TextureName = m_textureName;
		utils::DebugTools::AddString(m_tempTextureName, "Texture path", m_particleEmitter->GetDebugMenuName());
		utils::DebugTools::Bar* bar = utils::DebugTools::GetBar(m_particleEmitter->GetDebugMenuName());
		
		
		TwAddButton(bar->bar, "Browse Textures", Helper::BrowseTextures, m_particleEmitter, "label='Browse Textures'");
		TwAddButton(bar->bar, "Play/Pause", Helper::PauseToggle, m_particleEmitter, "label='Play/Pause'");
		TwAddButton(bar->bar, "Restart", Helper::Restart, m_particleEmitter, "label='Restart System'");
		TwAddButton(bar->bar, "Export", Helper::SaveSystem, m_particleEmitter, "label='Export system'");
		TwAddButton(bar->bar, "Import", Helper::LoadSystem, m_particleEmitter, "label='Import system'");
		TwAddButton(bar->bar, "Close", Helper::CloseSystem, this, "label='Close System'");
		
		
	}



	void Update()
	{
		m_textureName = m_particleEmitter->GetTexture()->GetName();

		if (m_textureName != m_temp2TextureName)
		{
			m_temp2TextureName = m_textureName;
			m_tempTextureName = m_textureName;
		}

		if (m_tempTextureName != m_textureName)
		{
			m_temp2TextureName = m_tempTextureName;
			m_textureName = m_tempTextureName;
			m_particleEmitter->SetTexture(m_textureName);
			m_textureName = m_particleEmitter->GetTexture()->GetName();
		}
	}

private:
	std::string m_textureName;
	std::string m_tempTextureName;
	std::string m_temp2TextureName;
	component::ParticleEmitterComponent* m_particleEmitter;
};