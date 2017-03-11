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
	std::string date(buffer);

	//Writing to the highscore file
	std::ofstream writeFile("../res/GUI/Highscore/score.txt");
	if (writeFile.is_open())
	{
		writeFile << std::to_string(m_scoreReader.size()) + "\n";
		for (auto it : m_scoreReader)
		{
			writeFile << it.name + "\n";
			writeFile << it.gold + "\n";
			writeFile << it.level + "\n";
			writeFile << date + "\n";
		}
		writeFile.close();
	}
}

void HighscoreMenuObject::ReadUserDataFromFile()
{
	std::ifstream readFile("../res/GUI/Highscore/score.txt");

	std::string tempName;
	std::string tempGold;
	std::string tempLevel;
	std::string tempDate;
	std::string line;
	int amountOfEntries;
	std::getline(readFile, line);
	amountOfEntries = std::stoi(line);
	for (int i = 0; i < amountOfEntries; i++)
	{
		std::getline(readFile, tempName);
		std::getline(readFile, tempGold);
		std::getline(readFile, tempLevel);
		std::getline(readFile, tempDate);
		m_scoreReader.push_back(ScoreLayout(tempName, tempLevel, tempGold, tempDate));
	}
	readFile.close();
}

void HighscoreMenuObject::Start()
{
	AddComponent<component::Camera>();
	m_highscoreBackground = AddComponent<component::SpriteComponent>();
	m_centText = AddComponent<component::SpriteComponent>();
	m_exitText = AddComponent<component::SpriteComponent>();
	m_inputMarker = AddComponent<component::TextComponent>();

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
	m_exitText->SetPositionY(950);
	m_exitText->SetScale(math::Vector2(1.0f, 1.0f));
	m_exitText->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_exitText->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_exitText->SetInteractable(true);

	m_inputMarker->SetFont("Highscore");
	m_inputMarker->SetOutput("-");
	m_inputMarker->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
	m_inputMarker->SetRotation(0.0f);
	m_inputMarker->SetScale(1.0f);
	m_inputMarker->SetPositionX(130);
	m_inputMarker->SetPositionY(0);
	m_inputMarker->SetDropshadow(false);
	m_inputMarker->SetOutline(true);
	m_inputMarker->SetOrigin(false);
	m_inputMarker->SetActive(false);

	ReadUserDataFromFile();
	int scoreSmallerThan = 0;
	if (ShipStats::s_playerDied)
	{
		if (m_scoreReader.size() > 0)
		{
			for (auto it : m_scoreReader)
			{
				if (std::stof(it.gold) > ShipStats::GetTotalGold())
				{
					scoreSmallerThan++;
				}
			}
		}

		bool addPlayerToHighScore = true;
		if (scoreSmallerThan > 7)
			addPlayerToHighScore = false;


		if (addPlayerToHighScore)
		{
			if (m_scoreReader.size() == 8)
			{
				m_scoreReader.pop_back();
			}
			time_t rawtime;
			struct tm * timeinfo;
			char buffer[80];


			time(&rawtime);
			timeinfo = localtime(&rawtime);

			strftime(buffer, 80, "%Y-%m-%d", timeinfo);
			std::string str(buffer);
			m_scoreReader.push_back(ScoreLayout("", std::to_string(ShipStats::s_currentLevel), std::to_string((int)ShipStats::GetTotalGold()), str));
		}
	}

	std::sort(m_scoreReader.begin(), m_scoreReader.end());

	for (int i = 0; i < m_scoreReader.size(); i++)
	{
		if (m_scoreReader[i].name == "")
		{
			m_playerIndex = i;
			break;
		}
		m_playerIndex = -1;
	}


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
		m_levels[i]->SetPositionY(m_nameYOffset + (i * 50) + 30);
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
	static bool done = false;
	std::string inputString;
	if (ShipStats::s_playerDied)
	{
		if (!done)
			//inputString = Input::GetKeyDown();	//What?

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

		if (m_playerIndex != -1 && !done)
		{
			m_names[m_playerIndex]->SetOutput(playerName);
			m_scoreReader[m_playerIndex].name = playerName;
			m_inputMarker->SetActive(true);
			m_inputMarker->SetPositionY(m_names[m_playerIndex]->GetPosition().y);
		}

		if (Input::GetKeyDown(Input::Keys::Enter) && !done)
		{
			done = true;
			ShipStats::s_playerDied = false;
			m_inputMarker->SetActive(false);
			WriteUserDataToFile();
		}

	}
	if (Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK) || Input::GetButtonDown(Input::Buttons::B))
	{
		Scene::LoadScene<MenuScene>();
		done = false;
		playerName = "";
	}
}


