#include "HighscoreMenuObject.h"
#include "../scenes/MenuScene.h"

void HighscoreMenuObject::Start()
{
	AddComponent<component::Camera>();
	m_highscoreBackground = AddComponent<component::SpriteComponent>();
	m_centText = AddComponent<component::SpriteComponent>();

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
