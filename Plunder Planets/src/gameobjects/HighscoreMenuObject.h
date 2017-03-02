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
	component::SpriteComponent* m_centText;
	component::TextComponent* m_name1;
	component::TextComponent* m_name2;
	component::TextComponent* m_name3;
	component::TextComponent* m_level1;
	component::TextComponent* m_level2;
	component::TextComponent* m_level3;
	component::TextComponent* m_gold1;
	component::TextComponent* m_gold2;
	component::TextComponent* m_gold3;
	component::TextComponent* m_date1;
	component::TextComponent* m_date2;
	component::TextComponent* m_date3;

	float m_nameYOffset = 290;
};


