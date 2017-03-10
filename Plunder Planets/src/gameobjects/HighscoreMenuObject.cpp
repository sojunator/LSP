#define _CRT_SECURE_NO_WARNINGS

#include "HighscoreMenuObject.h"
#include "../scenes/MenuScene.h"
#include <fstream>
#include <ctime>

void HighscoreMenuObject::WriteUserDataToFile()
{
	//Get the date
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%Y-%m-%d", timeinfo);
	std::string str(buffer);

	//Writing to the highscore file
	std::ofstream writeFile("../res/GUI/Highscore/score.txt", std::ios::app);
	if (writeFile.is_open())
	{
		writeFile << "n User\n";
		writeFile << "l 18\n";
		writeFile << "g 1500\n";
		writeFile << "d " << buffer << "\n";
		writeFile << "*\n";
		writeFile.close();
	}
}

void HighscoreMenuObject::ReadUserDataFromFile()
{
	//Read highscore file, text file for now
	std::string line;
	std::ifstream readFile("../res/GUI/Highscore/score.txt");

	while (!readFile.eof())
	{
		getline(readFile, line);
		if (line[0] == 'n')
		{
			for (int i = 0; i < 2; i++)
			{
				line.erase(line.begin());
			}
			m_tempName.push_back(line);
		}

		getline(readFile, line);
		if (line[0] == 'l')
		{
			for (int i = 0; i < 2; i++)
			{
				line.erase(line.begin());
			}
			m_tempLevel.push_back(line);
		}

		getline(readFile, line);
		if (line[0] == 'g')
		{
			for (int i = 0; i < 2; i++)
			{
				line.erase(line.begin());
			}
			m_tempGold.push_back(line);
		}

		getline(readFile, line);
		if (line[0] == 'd')
		{
			for (int i = 0; i < 2; i++)
			{
				line.erase(line.begin());
			}
			m_tempDate.push_back(line);
		}

		getline(readFile, line);
		if (line[0] == '*')
		{
			m_amount.push_back(1);
		}
	}
	readFile.close();

	for (unsigned int i = 0; i < m_amount.size(); i++)
	{
		m_scoreReader.push_back(ScoreLayout(m_tempName[i], m_tempLevel[i], m_tempGold[i], m_tempDate[i]));
	}
}

void HighscoreMenuObject::Start()
{
	AddComponent<component::Camera>();
	m_highscoreBackground = AddComponent<component::SpriteComponent>();
	m_centText = AddComponent<component::SpriteComponent>();
	m_exitText = AddComponent<component::SpriteComponent>();

	for (int i = 0; i < 8; i++)
	{
		m_names.push_back(AddComponent<component::TextComponent>());
		m_levels.push_back(AddComponent<component::TextComponent>());
		m_gold.push_back(AddComponent<component::TextComponent>());
		m_date.push_back(AddComponent<component::TextComponent>());
	}

	m_highscoreBackground->SetName("HighscoreBackground");
	m_highscoreBackground->SetPositionX(0);
	m_highscoreBackground->SetPositionY(0);
	m_highscoreBackground->SetScale(math::Vector2(1.0f, 1.0f));
	m_highscoreBackground->SetColor(math::Color(1.0f, 1.0f, 1.0f));

	m_centText->SetName("centText");
	m_centText->SetPositionX((Window::GetWidth() / 2) - 125);
	m_centText->SetPositionY(10);
	m_centText->SetScale(math::Vector2(1.0f, 1.0f));
	m_centText->SetColor(math::Color(1.0f, 1.0f, 1.0f));

	m_exitText->SetName("HighscoreExit");
	m_exitText->SetPositionX(50);
	m_exitText->SetPositionY(970);
	m_exitText->SetScale(math::Vector2(1.0f, 1.0f));
	m_exitText->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_exitText->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_exitText->SetInteractable(true);

	ReadUserDataFromFile();
	int scoreSmallerThan = 0;

	for (auto it : m_scoreReader)
	{
		if (std::stof(it.gold) > ShipStats::GetTotalGold())
		{
			scoreSmallerThan++;
		}
	}

	bool addPlayerToHighScore = true;
	if (scoreSmallerThan > 7)
		addPlayerToHighScore = false;



	for (int i = 0; i < m_scoreReader.size(); i++)
	{
		//Name
		m_names[i]->SetFont("Highscore");
		m_names[i]->SetOutput(m_scoreReader[i].name);
		m_names[i]->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_names[i]->SetRotation(0.0f);
		m_names[i]->SetScale(1.0f);
		m_names[i]->SetPositionX(142);
		m_names[i]->SetPositionY(m_nameYOffset + (i * 50) + 20);
		m_names[i]->SetDropshadow(false);
		m_names[i]->SetOutline(true);
		m_names[i]->SetOrigin(false);

		//Level1
		m_levels[i]->SetFont("Highscore");
		m_levels[i]->SetOutput(m_scoreReader[i].level);
		m_levels[i]->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_levels[i]->SetRotation(0.0f);
		m_levels[i]->SetScale(1.0f);
		m_levels[i]->SetPositionX(535);
		m_levels[i]->SetPositionY(m_nameYOffset + (i * 50) + 20);
		m_levels[i]->SetDropshadow(false);
		m_levels[i]->SetOutline(true);
		m_levels[i]->SetOrigin(true);

		//Gold1
		m_gold[i]->SetFont("Highscore");
		m_gold[i]->SetOutput(m_scoreReader[i].gold);
		m_gold[i]->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold[i]->SetRotation(0.0f);
		m_gold[i]->SetScale(1.0f);
		m_gold[i]->SetPositionX(890);
		m_gold[i]->SetPositionY(m_nameYOffset + 20 + (i * 50) + 20);
		m_gold[i]->SetDropshadow(false);
		m_gold[i]->SetOutline(true);
		m_gold[i]->SetOrigin(true);

		//Date1
		m_date[i]->SetFont("Highscore");
		m_date[i]->SetOutput(m_scoreReader[i].date);
		m_date[i]->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date[i]->SetRotation(0.0f);
		m_date[i]->SetScale(1.0f);
		m_date[i]->SetPositionX(1155);
		m_date[i]->SetPositionY(m_nameYOffset + (i * 50) + 20);
		m_date[i]->SetDropshadow(false);
		m_date[i]->SetOutline(true);
		m_date[i]->SetOrigin(false);
	}
}

void HighscoreMenuObject::Update()
{
	static std::string playerName;
	std::string inputString = Input::GetKeyDown();
	if (inputString == "-1")
	{
		if (playerName.size() > 0) // if it looks stupid it probably is
		{
			playerName.pop_back();
		}
	}
	else if (inputString == "0")
	{

	}
	else
	{
		playerName += inputString;
	}

	if (Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK) || Input::GetButtonDown(Input::Buttons::B))
		Scene::LoadScene<MenuScene>();

}


