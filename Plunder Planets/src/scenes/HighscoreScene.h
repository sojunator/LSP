#pragma once
#include "Thomas.h"
#include "../gameobjects/HighscoreMenuObject.h"

class HighscoreScene : public thomas::Scene
{
public:
	HighscoreScene() : Scene("HighscoreScene")
	{
		if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("HighscoreBackground", "../res/GUI/Highscore/highscore.jpg");
			thomas::graphics::Sprite::LoadTexture("centText", "../res/GUI/Highscore/centText.png");

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_1610)
		{

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_43)
		{

		}
		else
		{
			thomas::graphics::Sprite::LoadTexture("HighscoreBackground", "../res/GUI/Highscore/highscore.jpg");
			thomas::graphics::Sprite::LoadTexture("centText", "../res/GUI/Highscore/centText.png");
		}

		thomas::graphics::TextRender::LoadFont("Highscore", "../res/font/score.spritefont");

		LoadObject<HighscoreMenuObject>();

	};
};
