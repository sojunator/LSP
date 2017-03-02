#define _CRT_SECURE_NO_WARNINGS

#include "HighscoreMenuObject.h"
#include "../scenes/MenuScene.h"
#include <fstream>

void HighscoreMenuObject::Start()
{
	AddComponent<component::Camera>();
	m_highscoreBackground = AddComponent<component::SpriteComponent>();
	m_centText = AddComponent<component::SpriteComponent>();
	m_name1 = AddComponent<component::TextComponent>();
	m_name2 = AddComponent<component::TextComponent>();
	m_name3 = AddComponent<component::TextComponent>();
	m_level1 = AddComponent<component::TextComponent>();
	m_level2 = AddComponent<component::TextComponent>();
	m_level3 = AddComponent<component::TextComponent>();
	m_gold1 = AddComponent<component::TextComponent>();
	m_gold2 = AddComponent<component::TextComponent>();
	m_gold3 = AddComponent<component::TextComponent>();
	m_date1 = AddComponent<component::TextComponent>();
	m_date2 = AddComponent<component::TextComponent>();
	m_date3 = AddComponent<component::TextComponent>();

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
		m_date1->SetPositionX(1120);
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
		m_date2->SetPositionX(1120);
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
		m_date3->SetPositionX(1120);
		m_date3->SetPositionY(m_nameYOffset + 80);
		m_date3->SetDropshadow(false);
		m_date3->SetOutline(true);
		m_date3->SetOrigin(false);
	}

}

void HighscoreMenuObject::Update()
{
	//if (Input::GetMouseButtonDown(Input::MouseButtons::LEFT))
	//{
	//	if (m_exitButton->isHovering())
	//		ThomasCore::Exit();

	//	if (m_startButton->isHovering())
	//	{
	//		Scene::LoadScene<UpgradeScene>();
	//	}

	//	//Highscore
	//}

	if (Input::GetKeyDown(Input::Keys::Escape))
		Scene::LoadScene<MenuScene>();

	/*if (Input::GetKeyDown(Input::Keys::Enter))
		Scene::LoadScene<UpgradeScene>();*/
}
