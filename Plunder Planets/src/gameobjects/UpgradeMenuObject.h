#pragma once
#pragma once

#include <Thomas.h>
#include <string>

using namespace thomas;
using namespace object;
class UpgradeMenuObject : public GameObject
{

private:

public:
	UpgradeMenuObject() : GameObject("UpgradeMenuObject")
	{

	}
	~UpgradeMenuObject()
	{
	}

	void Start();


	void Update();



private:
	component::SpriteComponent* m_startButton;
	/*component::SpriteComponent* m_highScoreButton;
	component::SpriteComponent* m_optionButton;
	component::SpriteComponent* m_creditsButton;*/
	component::SpriteComponent* m_exitButton;
	component::SpriteComponent* m_backgrounds;
	component::SoundComponent* m_music;

};
