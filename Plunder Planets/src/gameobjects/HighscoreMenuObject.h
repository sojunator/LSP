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
	component::SpriteComponent* m_highscoreBackground;
};


