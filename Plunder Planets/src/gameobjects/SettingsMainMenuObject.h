#pragma once

#include <Thomas.h>
#include "ShipStats.h"

using namespace thomas;
using namespace object;
class SettingsMainMenuObject : public GameObject
{

private:

public:
	SettingsMainMenuObject() : GameObject("SettingsMainMenuObject")
	{

	}
	~SettingsMainMenuObject()
	{
	}

	void Start();
	void CheckInput();
	void SetTextActive();
	void Choice();
	void Update();


private:
	component::Camera* fov;
	component::SoundComponent* m_music;

	component::SpriteComponent* m_background;
	component::SpriteComponent* m_startButton;
	component::SpriteComponent* m_exitButton;
	component::TextComponent* m_settingsHeader;
	component::TextComponent* m_settingsHeadLine;
	component::TextComponent* m_settingsCamRotateX;
	component::TextComponent* m_settingsCamRotateY;
	component::TextComponent* m_settingsFovMin;
	component::TextComponent* m_settingsFovPlus;
	component::TextComponent* m_settingsFov;

	float m_inputDelay;
	bool m_firstTimeHax;
	bool m_camRotXActive;
	bool m_camRotYActive;
	bool m_fovMinActive;
	bool m_fovPlusActive;
};
