#include "MainMenuObject.h"
//#include "../scenes/GameScene.h"
#include "../scenes/UpgradeScene.h"
void MainMenuObject::Start()
{
	m_backgrounds = AddComponent<component::SpriteComponent>();
	m_camera = AddComponent<component::Camera>();
	m_startButton = AddComponent<component::SpriteComponent>();
	m_highScoreButton = AddComponent<component::SpriteComponent>();
	m_optionButton = AddComponent<component::SpriteComponent>();
	m_creditsButton = AddComponent<component::SpriteComponent>();
	m_exitButton = AddComponent<component::SpriteComponent>();
	m_music = AddComponent<component::SoundComponent>();

	m_yArray[0] = 1;

	m_music->SetClip("mMenuTheme");
	m_music->SetLooping(true);
	m_music->Play();

	m_startButton->SetName("MainMenuStart");
	m_startButton->SetPositionX(150);
	m_startButton->SetPositionY(60);
	m_startButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_startButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_startButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_startButton->SetInteractable(true);
	m_startButton->SetHovering(true);

	m_highScoreButton->SetName("MainMenuHighScore");
	m_highScoreButton->SetPositionX(150);
	m_highScoreButton->SetPositionY(160);
	m_highScoreButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_highScoreButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_highScoreButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_highScoreButton->SetInteractable(true);

	m_optionButton->SetName("MainMenuOptions");
	m_optionButton->SetPositionX(150);
	m_optionButton->SetPositionY(260);
	m_optionButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_optionButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_optionButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_optionButton->SetInteractable(true);

	m_creditsButton->SetName("MainMenuCredits");
	m_creditsButton->SetPositionX(150);
	m_creditsButton->SetPositionY(350);
	m_creditsButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_creditsButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_creditsButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_creditsButton->SetInteractable(true);

	m_exitButton->SetName("MainMenuExit");
	m_exitButton->SetPositionX(150);
	m_exitButton->SetPositionY(450);
	m_exitButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_exitButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_exitButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_exitButton->SetInteractable(true);

	m_backgrounds->SetName("MainMenuBackground");
	m_backgrounds->SetPositionX(0);
	m_backgrounds->SetPositionY(0);
	m_backgrounds->SetScale(math::Vector2(1.0f, 1.0f));
	m_backgrounds->SetColor(math::Color(1.0f, 1.0f, 1.0f));
}

void MainMenuObject::Update()
{
	for (int i = 0; i < 5; i++)
	{
		if (m_yArray[i] == 1)
		{
			if (i == 0)
				m_startButton->SetHovering(true);
		}
		else
			m_yArray[i] = 0;
	}
	m_yArray[0];
	if (Input::GetButton(Input::Buttons::A))
	{
		if (m_exitButton->isHovering())
			ThomasCore::Exit();

		if (m_startButton->isHovering())
		{
			Scene::LoadScene<UpgradeScene>();
		}
	}

	if (Input::GetKeyDown(Input::Keys::Escape))
		ThomasCore::Exit();

	if (Input::GetKeyDown(Input::Keys::Enter))
		Scene::LoadScene<UpgradeScene>();
}
