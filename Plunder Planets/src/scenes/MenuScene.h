#pragma once
#include "Thomas.h"
#include "../gameobjects/MainMenuObject.h"
#include "../gameobjects/ShipStats.h"
class MenuScene : public thomas::Scene
{
public:
	MenuScene() : Scene("MenuScene")
	{
		ShipStats::s_currentLevel = 0;
		//Reset Upgrades/Gold
		ShipStats::s_playerStats->SetCurrentGold(10000);
		ShipStats::s_playerStats->SetCannonDamage(5);
		ShipStats::s_playerStats->SetSpeed(50);
		ShipStats::s_playerStats->SetBoostCost(20);
		ShipStats::s_playerStats->SetCannonCost(50);
		ShipStats::s_playerStats->SetShieldAmount(0);
		ShipStats::s_playerStats->SetCurrentHealth(1);
		ShipStats::s_playerStats->SetPlunderSpeed(30);
		ShipStats::s_playerStats->SetCannonCounter(0);
		ShipStats::s_playerStats->SetMovementCounter(0);
		ShipStats::s_playerStats->SetResourceCounter(0);
		ShipStats::s_playerStats->SetShieldCounter(0);
		ShipStats::s_playerStats->SetPlunderCounter(0);

		if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("MainMenuStart", "../res/GUI/menu/start.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuHighScore", "../res/GUI/menu/highscore.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuOptions", "../res/GUI/menu/options.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuCredits", "../res/GUI/menu/credits.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuExit", "../res/GUI/menu/exit1.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuBackground", "../res/GUI/menu/background.png");

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_1610)
		{

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_43)
		{

		}
		else
		{
			thomas::graphics::Sprite::LoadTexture("MainMenuStart", "../res/GUI/menu/start.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuHighScore", "../res/GUI/menu/highscore.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuOptions", "../res/GUI/menu/options.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuCredits", "../res/GUI/menu/credits.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuExit", "../res/GUI/menu/exit.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuBackground", "../res/GUI/menu/background.png");
		}

		LoadObject<MainMenuObject>();

	};
};