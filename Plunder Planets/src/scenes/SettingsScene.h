#pragma once
#include "Thomas.h"
#include "../gameobjects/SettingsMainMenuObject.h"

class SettingsScene : public thomas::Scene
{
public:
	SettingsScene() : Scene("SettingsScene")
	{
		LoadShader("particleShader", thomas::graphics::Shader::InputLayouts::NONE, "../res/shaders/particleShader.hlsl");
		if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("Background", "../res/GUI/settings/background.jpg");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_1610) //FIX FITTING LATER
		{
		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_43)
		{
		}
		else
		{
			//thomas::graphics::Sprite::LoadTexture("CannonInfo", "../res/GUI/upgrade/cannoninfo.png");
		}
		thomas::graphics::TextRender::LoadFont("Pirate", "../res/font/pirate.spritefont");
		LoadObject<SettingsMainMenuObject>();

	};
};