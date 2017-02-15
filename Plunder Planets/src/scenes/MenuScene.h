#pragma once
#include "Thomas.h"
#include "../gameobjects/MainMenuObject.h"
class MenuScene : public thomas::Scene
{
public:
	MenuScene() : Scene("MenuScene")
	{
		if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("MainMenuStart", "../res/GUI/menu/start.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuHighScore", "../res/GUI/menu/highscore.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuOptions", "../res/GUI/menu/options.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuCredits", "../res/GUI/menu/credits.png");
			thomas::graphics::Sprite::LoadTexture("MainMenuExit", "../res/GUI/menu/exit.png");
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

		thomas::object::GameObject::Instantiate<MainMenuObject>(this);

	};
};