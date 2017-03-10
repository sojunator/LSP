#define _CRT_SECURE_NO_WARNINGS

#include "HighscoreMenuObject.h"
#include "../scenes/MenuScene.h"

#include <fstream>
#include <ctime>

void HighscoreMenuObject::Start()
{
	AddComponent<component::Camera>();
	m_highscoreBackground = AddComponent<component::SpriteComponent>();
	m_centText = AddComponent<component::SpriteComponent>();
	m_exitText = AddComponent<component::SpriteComponent>();
	m_music = AddComponent<component::SoundComponent>();

	m_music->SetClip("mMenuTheme");
	m_music->SetLooping(true);
	m_music->Play();

	//Names
	m_name1 = AddComponent<component::TextComponent>();
	m_name2 = AddComponent<component::TextComponent>();
	m_name3 = AddComponent<component::TextComponent>();
	m_name4 = AddComponent<component::TextComponent>();
	m_name5 = AddComponent<component::TextComponent>();
	m_name6 = AddComponent<component::TextComponent>();
	m_name7 = AddComponent<component::TextComponent>();
	m_name8 = AddComponent<component::TextComponent>();

	//Levels
	m_level1 = AddComponent<component::TextComponent>();
	m_level2 = AddComponent<component::TextComponent>();
	m_level3 = AddComponent<component::TextComponent>();
	m_level4 = AddComponent<component::TextComponent>();
	m_level5 = AddComponent<component::TextComponent>();
	m_level6 = AddComponent<component::TextComponent>();
	m_level7 = AddComponent<component::TextComponent>();
	m_level8 = AddComponent<component::TextComponent>();

	//Gold
	m_gold1 = AddComponent<component::TextComponent>();
	m_gold2 = AddComponent<component::TextComponent>();
	m_gold3 = AddComponent<component::TextComponent>();
	m_gold4 = AddComponent<component::TextComponent>();
	m_gold5 = AddComponent<component::TextComponent>();
	m_gold6 = AddComponent<component::TextComponent>();
	m_gold7 = AddComponent<component::TextComponent>();
	m_gold8 = AddComponent<component::TextComponent>();
	
	//Date
	m_date1 = AddComponent<component::TextComponent>();
	m_date2 = AddComponent<component::TextComponent>();
	m_date3 = AddComponent<component::TextComponent>();
	m_date4 = AddComponent<component::TextComponent>();
	m_date5 = AddComponent<component::TextComponent>();
	m_date6 = AddComponent<component::TextComponent>();
	m_date7 = AddComponent<component::TextComponent>();
	m_date8 = AddComponent<component::TextComponent>();

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


	////Get the date
	//time_t rawtime;
	//struct tm * timeinfo;
	//char buffer[80];

	//time(&rawtime);
	//timeinfo = localtime(&rawtime);

	//strftime(buffer, 80, "%Y-%m-%d", timeinfo);
	//std::string str(buffer);

	////Writing to the highscore file
	//std::ofstream writeFile("../res/GUI/Highscore/score.txt", std::ios::app);
	//if (writeFile.is_open())
	//{
	//	writeFile << "n User\n";
	//	writeFile << "l 18\n";
	//	writeFile << "g 1500\n";
	//	writeFile << "d " << buffer << "\n";
	//	writeFile << "*\n";
	//	writeFile.close();
	//}

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

	//Sort the vector after level
	std::sort(m_scoreReader.begin(), m_scoreReader.end(), myObject);

	//User1
	if (m_amount.size() == 1 || m_amount.size() > 1)
	{
		//Name1
		m_name1->SetFont("Highscore");
		m_name1->SetOutput(m_scoreReader[0].name);
		m_name1->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_name1->SetRotation(0.0f);
		m_name1->SetScale(1.0f);
		m_name1->SetPositionX(142);
		m_name1->SetPositionY(m_nameYOffset);
		m_name1->SetDropshadow(false);
		m_name1->SetOutline(true);
		m_name1->SetOrigin(false);

		//Level1
		m_level1->SetFont("Highscore");
		m_level1->SetOutput(m_scoreReader[0].level);
		m_level1->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_level1->SetRotation(0.0f);
		m_level1->SetScale(1.0f);
		m_level1->SetPositionX(535);
		m_level1->SetPositionY(m_nameYOffset + 20);
		m_level1->SetDropshadow(false);
		m_level1->SetOutline(true);
		m_level1->SetOrigin(true);

		//Gold1
		m_gold1->SetFont("Highscore");
		m_gold1->SetOutput(m_scoreReader[0].gold);
		m_gold1->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold1->SetRotation(0.0f);
		m_gold1->SetScale(1.0f);
		m_gold1->SetPositionX(890);
		m_gold1->SetPositionY(m_nameYOffset + 20);
		m_gold1->SetDropshadow(false);
		m_gold1->SetOutline(true);
		m_gold1->SetOrigin(true);

		//Date1
		m_date1->SetFont("Highscore");
		m_date1->SetOutput(m_scoreReader[0].date);
		m_date1->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date1->SetRotation(0.0f);
		m_date1->SetScale(1.0f);
		m_date1->SetPositionX(1155);
		m_date1->SetPositionY(m_nameYOffset);
		m_date1->SetDropshadow(false);
		m_date1->SetOutline(true);
		m_date1->SetOrigin(false);
	}

	//User2
	if (m_amount.size() == 2 || m_amount.size() > 1)
	{
		//Name2
		m_name2->SetFont("Highscore");
		m_name2->SetOutput(m_scoreReader[1].name);
		m_name2->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_name2->SetRotation(0.0f);
		m_name2->SetScale(1.0f);
		m_name2->SetPositionX(142);
		m_name2->SetPositionY(m_nameYOffset + 40);
		m_name2->SetDropshadow(false);
		m_name2->SetOutline(true);
		m_name2->SetOrigin(false);

		//Level2
		m_level2->SetFont("Highscore");
		m_level2->SetOutput(m_scoreReader[1].level);
		m_level2->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_level2->SetRotation(0.0f);
		m_level2->SetScale(1.0f);
		m_level2->SetPositionX(535);
		m_level2->SetPositionY(m_nameYOffset + 60);
		m_level2->SetDropshadow(false);
		m_level2->SetOutline(true);
		m_level2->SetOrigin(true);

		//Gold2
		m_gold2->SetFont("Highscore");
		m_gold2->SetOutput(m_scoreReader[1].gold);
		m_gold2->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold2->SetRotation(0.0f);
		m_gold2->SetScale(1.0f);
		m_gold2->SetPositionX(890);
		m_gold2->SetPositionY(m_nameYOffset + 60);
		m_gold2->SetDropshadow(false);
		m_gold2->SetOutline(true);
		m_gold2->SetOrigin(true);

		//Date2
		m_date2->SetFont("Highscore");
		m_date2->SetOutput(m_scoreReader[1].date);
		m_date2->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date2->SetRotation(0.0f);
		m_date2->SetScale(1.0f);
		m_date2->SetPositionX(1155);
		m_date2->SetPositionY(m_nameYOffset + 40);
		m_date2->SetDropshadow(false);
		m_date2->SetOutline(true);
		m_date2->SetOrigin(false);
	}

	//User3
	if (m_amount.size() == 3 || m_amount.size() > 2)
	{
		//Name3
		m_name3->SetFont("Highscore");
		m_name3->SetOutput(m_scoreReader[2].name);
		m_name3->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_name3->SetRotation(0.0f);
		m_name3->SetScale(1.0f);
		m_name3->SetPositionX(142);
		m_name3->SetPositionY(m_nameYOffset + 80);
		m_name3->SetDropshadow(false);
		m_name3->SetOutline(true);
		m_name3->SetOrigin(false);

		//Level3
		m_level3->SetFont("Highscore");
		m_level3->SetOutput(m_scoreReader[2].level);
		m_level3->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_level3->SetRotation(0.0f);
		m_level3->SetScale(1.0f);
		m_level3->SetPositionX(535);
		m_level3->SetPositionY(m_nameYOffset + 100);
		m_level3->SetDropshadow(false);
		m_level3->SetOutline(true);
		m_level3->SetOrigin(true);

		//Gold3
		m_gold3->SetFont("Highscore");
		m_gold3->SetOutput(m_scoreReader[2].gold);
		m_gold3->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold3->SetRotation(0.0f);
		m_gold3->SetScale(1.0f);
		m_gold3->SetPositionX(890);
		m_gold3->SetPositionY(m_nameYOffset + 100);
		m_gold3->SetDropshadow(false);
		m_gold3->SetOutline(true);
		m_gold3->SetOrigin(true);

		//Date3
		m_date3->SetFont("Highscore");
		m_date3->SetOutput(m_scoreReader[2].date);
		m_date3->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date3->SetRotation(0.0f);
		m_date3->SetScale(1.0f);
		m_date3->SetPositionX(1155);
		m_date3->SetPositionY(m_nameYOffset + 80);
		m_date3->SetDropshadow(false);
		m_date3->SetOutline(true);
		m_date3->SetOrigin(false);
	}

	//User4
	if (m_amount.size() == 4 || m_amount.size() > 3)
	{
		//Name4
		m_name4->SetFont("Highscore");
		m_name4->SetOutput(m_scoreReader[3].name);
		m_name4->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_name4->SetRotation(0.0f);
		m_name4->SetScale(1.0f);
		m_name4->SetPositionX(142);
		m_name4->SetPositionY(m_nameYOffset + 120);
		m_name4->SetDropshadow(false);
		m_name4->SetOutline(true);
		m_name4->SetOrigin(false);

		//Level4
		m_level4->SetFont("Highscore");
		m_level4->SetOutput(m_scoreReader[3].level);
		m_level4->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_level4->SetRotation(0.0f);
		m_level4->SetScale(1.0f);
		m_level4->SetPositionX(535);
		m_level4->SetPositionY(m_nameYOffset + 140);
		m_level4->SetDropshadow(false);
		m_level4->SetOutline(true);
		m_level4->SetOrigin(true);

		//Gold4
		m_gold4->SetFont("Highscore");
		m_gold4->SetOutput(m_scoreReader[3].gold);
		m_gold4->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold4->SetRotation(0.0f);
		m_gold4->SetScale(1.0f);
		m_gold4->SetPositionX(890);
		m_gold4->SetPositionY(m_nameYOffset + 140);
		m_gold4->SetDropshadow(false);
		m_gold4->SetOutline(true);
		m_gold4->SetOrigin(true);

		//Date4
		m_date4->SetFont("Highscore");
		m_date4->SetOutput(m_scoreReader[3].date);
		m_date4->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date4->SetRotation(0.0f);
		m_date4->SetScale(1.0f);
		m_date4->SetPositionX(1155);
		m_date4->SetPositionY(m_nameYOffset + 120);
		m_date4->SetDropshadow(false);
		m_date4->SetOutline(true);
		m_date4->SetOrigin(false);
	}

	//User5
	if (m_amount.size() == 5 || m_amount.size() > 4)
	{
		//Name5
		m_name5->SetFont("Highscore");
		m_name5->SetOutput(m_scoreReader[4].name);
		m_name5->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_name5->SetRotation(0.0f);
		m_name5->SetScale(1.0f);
		m_name5->SetPositionX(142);
		m_name5->SetPositionY(m_nameYOffset + 160);
		m_name5->SetDropshadow(false);
		m_name5->SetOutline(true);
		m_name5->SetOrigin(false);

		//Level5
		m_level5->SetFont("Highscore");
		m_level5->SetOutput(m_scoreReader[4].level);
		m_level5->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_level5->SetRotation(0.0f);
		m_level5->SetScale(1.0f);
		m_level5->SetPositionX(535);
		m_level5->SetPositionY(m_nameYOffset + 180);
		m_level5->SetDropshadow(false);
		m_level5->SetOutline(true);
		m_level5->SetOrigin(true);

		//Gold5
		m_gold5->SetFont("Highscore");
		m_gold5->SetOutput(m_scoreReader[4].gold);
		m_gold5->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold5->SetRotation(0.0f);
		m_gold5->SetScale(1.0f);
		m_gold5->SetPositionX(890);
		m_gold5->SetPositionY(m_nameYOffset + 180);
		m_gold5->SetDropshadow(false);
		m_gold5->SetOutline(true);
		m_gold5->SetOrigin(true);

		//Date5
		m_date5->SetFont("Highscore");
		m_date5->SetOutput(m_scoreReader[4].date);
		m_date5->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date5->SetRotation(0.0f);
		m_date5->SetScale(1.0f);
		m_date5->SetPositionX(1155);
		m_date5->SetPositionY(m_nameYOffset + 160);
		m_date5->SetDropshadow(false);
		m_date5->SetOutline(true);
		m_date5->SetOrigin(false);
	}

	//User6
	if (m_amount.size() == 6 || m_amount.size() > 5)
	{
		//Name6
		m_name6->SetFont("Highscore");
		m_name6->SetOutput(m_scoreReader[5].name);
		m_name6->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_name6->SetRotation(0.0f);
		m_name6->SetScale(1.0f);
		m_name6->SetPositionX(142);
		m_name6->SetPositionY(m_nameYOffset + 200);
		m_name6->SetDropshadow(false);
		m_name6->SetOutline(true);
		m_name6->SetOrigin(false);

		//Level6
		m_level6->SetFont("Highscore");
		m_level6->SetOutput(m_scoreReader[5].level);
		m_level6->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_level6->SetRotation(0.0f);
		m_level6->SetScale(1.0f);
		m_level6->SetPositionX(535);
		m_level6->SetPositionY(m_nameYOffset + 220);
		m_level6->SetDropshadow(false);
		m_level6->SetOutline(true);
		m_level6->SetOrigin(true);

		//Gold6
		m_gold6->SetFont("Highscore");
		m_gold6->SetOutput(m_scoreReader[5].gold);
		m_gold6->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold6->SetRotation(0.0f);
		m_gold6->SetScale(1.0f);
		m_gold6->SetPositionX(890);
		m_gold6->SetPositionY(m_nameYOffset + 220);
		m_gold6->SetDropshadow(false);
		m_gold6->SetOutline(true);
		m_gold6->SetOrigin(true);

		//Date6
		m_date6->SetFont("Highscore");
		m_date6->SetOutput(m_scoreReader[5].date);
		m_date6->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date6->SetRotation(0.0f);
		m_date6->SetScale(1.0f);
		m_date6->SetPositionX(1155);
		m_date6->SetPositionY(m_nameYOffset + 200);
		m_date6->SetDropshadow(false);
		m_date6->SetOutline(true);
		m_date6->SetOrigin(false);
	}

	//User7
	if (m_amount.size() == 7 || m_amount.size() > 6)
	{
		//Name7
		m_name7->SetFont("Highscore");
		m_name7->SetOutput(m_scoreReader[6].name);
		m_name7->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_name7->SetRotation(0.0f);
		m_name7->SetScale(1.0f);
		m_name7->SetPositionX(142);
		m_name7->SetPositionY(m_nameYOffset + 240);
		m_name7->SetDropshadow(false);
		m_name7->SetOutline(true);
		m_name7->SetOrigin(false);

		//Level7
		m_level7->SetFont("Highscore");
		m_level7->SetOutput(m_scoreReader[6].level);
		m_level7->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_level7->SetRotation(0.0f);
		m_level7->SetScale(1.0f);
		m_level7->SetPositionX(535);
		m_level7->SetPositionY(m_nameYOffset + 260);
		m_level7->SetDropshadow(false);
		m_level7->SetOutline(true);
		m_level7->SetOrigin(true);

		//Gold7
		m_gold7->SetFont("Highscore");
		m_gold7->SetOutput(m_scoreReader[6].gold);
		m_gold7->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold7->SetRotation(0.0f);
		m_gold7->SetScale(1.0f);
		m_gold7->SetPositionX(890);
		m_gold7->SetPositionY(m_nameYOffset + 260);
		m_gold7->SetDropshadow(false);
		m_gold7->SetOutline(true);
		m_gold7->SetOrigin(true);

		//Date7
		m_date7->SetFont("Highscore");
		m_date7->SetOutput(m_scoreReader[6].date);
		m_date7->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date7->SetRotation(0.0f);
		m_date7->SetScale(1.0f);
		m_date7->SetPositionX(1155);
		m_date7->SetPositionY(m_nameYOffset + 240);
		m_date7->SetDropshadow(false);
		m_date7->SetOutline(true);
		m_date7->SetOrigin(false);
	}

	//User8
	if (m_amount.size() == 8 || m_amount.size() > 7)
	{
		//Name8
		m_name8->SetFont("Highscore");
		m_name8->SetOutput(m_scoreReader[7].name);
		m_name8->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_name8->SetRotation(0.0f);
		m_name8->SetScale(1.0f);
		m_name8->SetPositionX(142);
		m_name8->SetPositionY(m_nameYOffset + 280);
		m_name8->SetDropshadow(false);
		m_name8->SetOutline(true);
		m_name8->SetOrigin(false);

		//Level8
		m_level8->SetFont("Highscore");
		m_level8->SetOutput(m_scoreReader[7].level);
		m_level8->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_level8->SetRotation(0.0f);
		m_level8->SetScale(1.0f);
		m_level8->SetPositionX(535);
		m_level8->SetPositionY(m_nameYOffset + 300);
		m_level8->SetDropshadow(false);
		m_level8->SetOutline(true);
		m_level8->SetOrigin(true);

		//Gold8
		m_gold8->SetFont("Highscore");
		m_gold8->SetOutput(m_scoreReader[7].gold);
		m_gold8->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_gold8->SetRotation(0.0f);
		m_gold8->SetScale(1.0f);
		m_gold8->SetPositionX(890);
		m_gold8->SetPositionY(m_nameYOffset + 300);
		m_gold8->SetDropshadow(false);
		m_gold8->SetOutline(true);
		m_gold8->SetOrigin(true);

		//Date8
		m_date8->SetFont("Highscore");
		m_date8->SetOutput(m_scoreReader[7].date);
		m_date8->SetColor(math::Vector3(0.0f, 0.0f, 0.0f));
		m_date8->SetRotation(0.0f);
		m_date8->SetScale(1.0f);
		m_date8->SetPositionX(1155);
		m_date8->SetPositionY(m_nameYOffset + 280);
		m_date8->SetDropshadow(false);
		m_date8->SetOutline(true);
		m_date8->SetOrigin(false);
	}
}

void HighscoreMenuObject::Update()
{
	if (Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK) || Input::GetButtonDown(Input::Buttons::B))
		Scene::LoadScene<MenuScene>();
}
