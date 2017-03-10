#pragma once
#include "Thomas.h"
#include "../gameobjects/CreditsMenuObject.h"

class CreditsScene : public thomas::Scene
{
public:
	CreditsScene() : Scene("CreditsScene")
	{
		LoadShader("particleShader", thomas::graphics::Shader::InputLayouts::NONE, "../res/shaders/particleShader.hlsl");
		if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_169)
		{
			thomas::graphics::Sprite::LoadTexture("Background", "../res/GUI/credits/credits.jpg");
			thomas::graphics::Sprite::LoadTexture("Exit", "../res/GUI/menu/exit.png");

		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_1610) //FIX FITTING LATER
		{
		}
		else if (thomas::Window::GetAspectRatio() == thomas::Window::Ratio::STANDARD_43)
		{
		}
		else
		{
			thomas::graphics::Sprite::LoadTexture("Background", "../res/GUI/credits/credits.jpg");
		}
		thomas::graphics::TextRender::LoadFont("Pirate", "../res/font/pirate.spritefont");
		LoadObject<CreditsMenuObject>();

	}
};