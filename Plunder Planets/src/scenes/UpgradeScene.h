#pragma once
#include "Thomas.h"
#include "../gameobjects/UpgradeMenuObject.h"
class UpgradeScene : public thomas::Scene
{
public:
	UpgradeScene() : Scene("UpgradeScene")
	{
		if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuStart", "../res/GUI/upgrade/continue.png");
			/*thomas::graphics::Sprite::LoadTexture("MainMenuHighScore", "../res/GUI/menu/highscore.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuOptions", "../res/GUI/menu/options.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuCredits", "../res/GUI/menu/credits.png");*/
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuBackground", "../res/GUI/upgrade/background.jpg");

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_1610)
		{

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_43)
		{

		}
		else
		{
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuStart", "../res/GUI/upgrade/continue.png");
			/*thomas::graphics::Sprite::LoadTexture("MainMenuHighScore", "../res/GUI/menu/highscore.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuOptions", "../res/GUI/menu/options.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuCredits", "../res/GUI/menu/credits.png");*/
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("UpgradeMenuBackground", "../res/GUI/upgrade/background.jpg");
		}

		LoadObject<UpgradeMenuObject>();

	};
};