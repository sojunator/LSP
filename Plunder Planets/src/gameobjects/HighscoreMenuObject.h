#pragma once

#include <Thomas.h>
#include <string>

using namespace thomas;
using namespace object;

class HighscoreMenuObject : public GameObject
{
private:
	struct ScoreLayout
	{
		ScoreLayout() {}
		ScoreLayout(std::string n, std::string l, std::string g, std::string d) : name(n), level(l), gold(g), date(d) {}

		std::string name;
		std::string level;
		std::string gold;
		std::string date;
	};

	struct myOperator
	{
		bool operator() (const ScoreLayout& x, const ScoreLayout& y) { return (x.level > y.level); }
	}myObject;

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
	component::SpriteComponent* m_exitText;

	//Names
	component::TextComponent* m_name1;
	component::TextComponent* m_name2;
	component::TextComponent* m_name3;
	component::TextComponent* m_name4;
	component::TextComponent* m_name5;
	component::TextComponent* m_name6;
	component::TextComponent* m_name7;
	component::TextComponent* m_name8;

	//Levels
	component::TextComponent* m_level1;
	component::TextComponent* m_level2;
	component::TextComponent* m_level3;
	component::TextComponent* m_level4;
	component::TextComponent* m_level5;
	component::TextComponent* m_level6;
	component::TextComponent* m_level7;
	component::TextComponent* m_level8;

	//Gold
	component::TextComponent* m_gold1;
	component::TextComponent* m_gold2;
	component::TextComponent* m_gold3;
	component::TextComponent* m_gold4;
	component::TextComponent* m_gold5;
	component::TextComponent* m_gold6;
	component::TextComponent* m_gold7;
	component::TextComponent* m_gold8;

	//Dates
	component::TextComponent* m_date1;
	component::TextComponent* m_date2;
	component::TextComponent* m_date3;
	component::TextComponent* m_date4;
	component::TextComponent* m_date5;
	component::TextComponent* m_date6;
	component::TextComponent* m_date7;
	component::TextComponent* m_date8;

	std::vector <std::string> m_tempName;
	std::vector <std::string> m_tempLevel;
	std::vector <std::string> m_tempGold;
	std::vector <std::string> m_tempDate;
	std::vector <int> m_amount;
	std::vector <ScoreLayout> m_scoreReader;

	float m_nameYOffset = 290;
};


