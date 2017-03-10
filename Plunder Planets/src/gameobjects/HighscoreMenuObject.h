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
		bool operator<(const ScoreLayout& x) {
			if (std::stoi(this->level) == std::stoi(x.level))
				return std::stoi(this->gold) > std::stoi(x.gold);
			return std::stoi(this->level) > std::stoi(x.level);
		}
	};

	struct myOperator
	{
		bool operator() (const ScoreLayout& x, const ScoreLayout& y) { return (x.level > y.level); }
	}myObject;

public:
	void WriteUserDataToFile();
	void ReadUserDataFromFile();

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
	std::vector<component::TextComponent*> m_names;

	//Levels
	std::vector<component::TextComponent*> m_levels;

	//Gold
	std::vector<component::TextComponent*> m_gold;

	//Dates
	std::vector<component::TextComponent*> m_date;

	//Input marker
	component::TextComponent* m_inputMarker;

	std::vector <ScoreLayout> m_scoreReader;

	float m_nameYOffset = 290;
	int m_playerIndex;
};


