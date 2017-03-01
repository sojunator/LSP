#pragma once

#include <Thomas.h>
#include <string>

using namespace thomas;
using namespace object;

class HighscoreMenuObject : public GameObject
{
private:

public:
	HighscoreMenuObject() : GameObject("HighscoreMenuObject")
	{

	}

	~HighscoreMenuObject()
	{

	}

	void Start();
	void Update();

private:
	/*component::Camera* m_camera;
	component::SpriteComponent* m_startButton;
	component::SpriteComponent* m_highScoreButton;
	component::SpriteComponent* m_optionButton;
	component::SpriteComponent* m_creditsButton;
	component::SpriteComponent* m_exitButton;
	component::SpriteComponent* m_backgrounds;
	component::SoundComponent* m_music*/;
};


