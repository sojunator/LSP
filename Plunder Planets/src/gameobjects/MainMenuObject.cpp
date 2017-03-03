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
	m_delay = m_delay - Time::GetDeltaTime();
	for (int i = 0; i < 5; i++) //Move to own function
	{
		if (m_yArray[i] == 1)
		{
			if (i == 0)
				m_startButton->SetHovering(true);
			if (i == 1)
				m_highScoreButton->SetHovering(true);
			if (i == 2)
				m_optionButton->SetHovering(true);
			if (i == 3)
				m_creditsButton->SetHovering(true);
			if (i == 4)
				m_exitButton->SetHovering(true);
		}
		else
		{
			if (i == 0)
				m_startButton->SetHovering(false);
			if (i == 1)
				m_highScoreButton->SetHovering(false);
			if (i == 2)
				m_optionButton->SetHovering(false);
			if (i == 3)
				m_creditsButton->SetHovering(false);
			if (i == 4)
				m_exitButton->SetHovering(false);
		}
			
	}
	if (Input::GetButtonDown(Input::Buttons::A) || Input::GetKey(Input::Keys::Enter))
	{
		if (m_startButton->isHovering())
		{
			Scene::LoadScene<UpgradeScene>();
		}

		if (m_highScoreButton->isHovering())
		{
			//Add Highscore
			//Scene::LoadScene<HighscoreScene>();
		}
		if (m_optionButton->isHovering())
		{
			//Add Settings
		}
		if (m_creditsButton->isHovering())
		{
			//Add Credits
		}

		if (m_exitButton->isHovering())
			ThomasCore::Exit();

	}

	//Menu scrolling, move to own function, LONG if() statement
	if ((Input::GetLeftStickY() && m_delay < 0.1f) || (Input::GetButton(Input::Buttons::DPAD_DOWN) && m_delay < 0.1f) 
		|| (Input::GetButton(Input::Buttons::DPAD_UP) && m_delay < 0.1f) || (Input::GetKey(Input::Keys::Down) && m_delay < 0.1f) 
		|| (Input::GetKey(Input::Keys::Up) && m_delay < 0.1f))
	{
		for (int i = 0; i < 5; i++)
		{
			if ((m_yArray[0] == 1) && ((Input::GetLeftStickY() > 0) || Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Up))) //Player presses up, we're already at the top
			{
				m_yArray[0] = 1;
				break;
			}
			else if (m_yArray[4] == 1 && ((Input::GetLeftStickY() < 0) || Input::GetButton(Input::Buttons::DPAD_DOWN))) //Player presses down, we're already at the bottom
			{
				m_yArray[4] = 1;
				break;
			}
			else if ((i > 0) && (m_yArray[i] == 1) && ((Input::GetLeftStickY() > 0) || Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Up))) //Player presses up
			{
				m_yArray[i - 1] = 1; //Select Sprite Above
				m_yArray[i] = 0; //Deselect Current Sprite
				break;
			}
			else if ((i < 4) && (m_yArray[i] == 1) && ((Input::GetLeftStickY() < 0) || Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetKey(Input::Keys::Down))) //Player presses down
			{
				m_yArray[i + 1] = 1;
				m_yArray[i] = 0;
				break;
			} 
		}
		m_delay = 0.3f;
	}
	if (Input::GetButtonDown(Input::Buttons::START))
		Scene::LoadScene<UpgradeScene>();

	if (Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK))
		ThomasCore::Exit();
}
