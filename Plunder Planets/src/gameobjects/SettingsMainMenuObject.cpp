#include "SettingsMainMenuObject.h"
#include "../scenes/GameScene.h"
#include "ShipStats.h"

void SettingsMainMenuObject::Start()
{
	//Set Camera
	component::Camera* cam = AddComponent<component::Camera>();
	cam->SetFov(50);

	//Set Music
	m_music = AddComponent<component::SoundComponent>();
	m_music->SetClip("mMenuTheme");
	m_music->SetLooping(true);
	m_music->Play();

	//Set background
	m_background = AddComponent<component::SpriteComponent>();
	m_background->SetName("Background");
	m_background->SetPositionX(0);
	m_background->SetPositionY(0);
	m_background->SetScale(math::Vector2(1.0f, 1.0f));
	m_background->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_background->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_background->SetInteractable(false);

	m_exitButton = AddComponent<component::SpriteComponent>();
	m_exitButton->SetName("UpgradeMenuExit");
	m_exitButton->SetPositionX(50);
	m_exitButton->SetPositionY(950);
	m_exitButton->SetScale(math::Vector2(1.0f, 1.0f));
	m_exitButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_exitButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
	m_exitButton->SetInteractable(true);

	m_settingsHeader = AddComponent<component::TextComponent>();
	m_settingsHeader->SetFont("Pirate");
	m_settingsHeader->SetOutput("Options");
	m_settingsHeader->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_settingsHeader->SetRotation(0.0f);
	m_settingsHeader->SetScale(2.0f);
	m_settingsHeader->SetPositionX((Window::GetWidth() / 2) - 250);
	m_settingsHeader->SetPositionY(50);
	m_settingsHeader->SetDropshadow(true);
	m_settingsHeader->SetOutline(true);
	m_settingsHeader->SetOrigin(false);

	m_settingsCamRotateX = AddComponent<component::TextComponent>();
	m_settingsCamRotateX->SetFont("Pirate");
	if(ShipStats::s_playerStats->GetInvertCamX() == -1)
		m_settingsCamRotateX->SetOutput("Invert Camera Rotation X (No)");
	else
		m_settingsCamRotateX->SetOutput("Invert Camera Rotation X (Yes)");
	m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_settingsCamRotateX->SetRotation(0.0f);
	m_settingsCamRotateX->SetScale(1.0f);
	m_settingsCamRotateX->SetPositionX((Window::GetWidth() / 4) - 400);
	m_settingsCamRotateX->SetPositionY(Window::GetHeight() / 4 - 30);
	m_settingsCamRotateX->SetDropshadow(true);
	m_settingsCamRotateX->SetOutline(true);
	m_settingsCamRotateX->SetOrigin(false);

	m_settingsCamRotateY = AddComponent<component::TextComponent>();
	m_settingsCamRotateY->SetFont("Pirate");
	if (ShipStats::s_playerStats->GetInvertCamY())
		m_settingsCamRotateY->SetOutput("Invert Camera Rotation Y (No)");
	else
		m_settingsCamRotateY->SetOutput("Invert Camera Rotation Y (Yes)");
	m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_settingsCamRotateY->SetRotation(0.0f);
	m_settingsCamRotateY->SetScale(1.0f);
	m_settingsCamRotateY->SetPositionX((Window::GetWidth() / 4) - 400);
	m_settingsCamRotateY->SetPositionY(Window::GetHeight() / 4 + 70);
	m_settingsCamRotateY->SetDropshadow(true);
	m_settingsCamRotateY->SetOutline(true);
	m_settingsCamRotateY->SetOrigin(false);

	m_settingsFovMin = AddComponent<component::TextComponent>();
	m_settingsFovMin->SetFont("Pirate");
	m_settingsFovMin->SetOutput("FOV-");
	m_settingsFovMin->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_settingsFovMin->SetRotation(0.0f);
	m_settingsFovMin->SetScale(1.0f);
	m_settingsFovMin->SetPositionX((Window::GetWidth() / 4) - 400);
	m_settingsFovMin->SetPositionY(Window::GetHeight() / 4 + 170);
	m_settingsFovMin->SetDropshadow(true);
	m_settingsFovMin->SetOutline(true);
	m_settingsFovMin->SetOrigin(false);

	m_settingsFovPlus = AddComponent<component::TextComponent>();
	m_settingsFovPlus->SetFont("Pirate");
	m_settingsFovPlus->SetOutput("FOV+");
	m_settingsFovPlus->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_settingsFovPlus->SetRotation(0.0f);
	m_settingsFovPlus->SetScale(1.0f);
	m_settingsFovPlus->SetPositionX((Window::GetWidth() / 4) - 100);
	m_settingsFovPlus->SetPositionY(Window::GetHeight() / 4 + 170);
	m_settingsFovPlus->SetDropshadow(true);
	m_settingsFovPlus->SetOutline(true);
	m_settingsFovPlus->SetOrigin(false);

	m_settingsFov = AddComponent<component::TextComponent>();
	int fovInt = ShipStats::s_playerStats->GetFOV();
	m_settingsFov->SetFont("Pirate");
	m_settingsFov->SetOutput(std::to_string(fovInt));
	m_settingsFov->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	m_settingsFov->SetRotation(0.0f);
	m_settingsFov->SetScale(1.0f);
	m_settingsFov->SetPositionX((Window::GetWidth() / 4) - 225);
	m_settingsFov->SetPositionY(Window::GetHeight() / 4 + 170);
	m_settingsFov->SetDropshadow(true);
	m_settingsFov->SetOutline(true);
	m_settingsFov->SetOrigin(false);

	m_camRotXActive = true;
	m_camRotYActive = false;
	m_fovMinActive = false;
	m_fovPlusActive = false;

	m_inputDelay = 0.0f; // so that we don't do 500 inputs per second.
	//HideMenu();
}

void SettingsMainMenuObject::CheckInput()
{
	if (m_inputDelay < 0.001f)
	{
		if (Input::GetButton(Input::Buttons::DPAD_DOWN) || (Input::GetLeftStickY() < -0.1f && abs(Input::GetLeftStickY()) > abs(Input::GetLeftStickX())) || Input::GetKey(Input::Keys::Down))
		{
			if (m_camRotXActive)
			{
				m_camRotXActive = false;
				m_camRotYActive = true;
				m_fovMinActive = false;
				m_fovPlusActive = false;
			}
			else if (m_camRotYActive)
			{
				m_camRotXActive = false;
				m_camRotYActive = false;
				m_fovMinActive = true;
				m_fovPlusActive = false;
			}
			else if (m_fovMinActive)
			{
				m_camRotXActive = true;
				m_camRotYActive = false;
				m_fovMinActive = false;
				m_fovPlusActive = false;
			}
			else if (m_fovPlusActive)
			{
				m_camRotXActive = true;
				m_camRotYActive = false;
				m_fovMinActive = false;
				m_fovPlusActive = false;
			}

			m_inputDelay = 0.3f;
		}

		if (Input::GetButton(Input::Buttons::DPAD_UP) || (Input::GetLeftStickY() > 0.1f && abs(Input::GetLeftStickY()) > abs(Input::GetLeftStickX())) || Input::GetKey(Input::Keys::Up))
		{
			if (m_camRotXActive)
			{
				m_camRotXActive = false;
				m_camRotYActive = false;
				m_fovMinActive = true;
				m_fovPlusActive = false;
			}
			else if (m_camRotYActive)
			{
				m_camRotXActive = true;
				m_camRotYActive = false;
				m_fovMinActive = false;
				m_fovPlusActive = false;
			}
			else if (m_fovMinActive)
			{
				m_camRotXActive = false;
				m_camRotYActive = true;
				m_fovMinActive = false;
				m_fovPlusActive = false;
			}
			else if (m_fovPlusActive)
			{
				m_camRotXActive = false;
				m_camRotYActive = true;
				m_fovMinActive = false;
				m_fovPlusActive = false;
			}

			m_inputDelay = 0.3f;
		}
		if (Input::GetButton(Input::Buttons::DPAD_LEFT) || (Input::GetLeftStickX() < -0.1f && abs(Input::GetLeftStickX()) > abs(Input::GetLeftStickY())) || Input::GetKey(Input::Keys::Left))
		{
			if (m_fovPlusActive)
			{
				m_camRotXActive = false;
				m_camRotYActive = false;
				m_fovMinActive = true;
				m_fovPlusActive = false;
			}
		}
		if (Input::GetButton(Input::Buttons::DPAD_RIGHT) || (Input::GetLeftStickX() > 0.1f && abs(Input::GetLeftStickX()) > abs(Input::GetLeftStickY())) || Input::GetKey(Input::Keys::Right))
		{
			if (m_fovMinActive)
			{
				m_camRotXActive = false;
				m_camRotYActive = false;
				m_fovMinActive = false;
				m_fovPlusActive = true;
			}
		}
	}
	else
	{
		m_inputDelay -= thomas::ThomasTime::GetActualDeltaTime();
	}
}

void SettingsMainMenuObject::SetTextActive()
{
	if (m_camRotXActive)
	{
		m_settingsCamRotateX->SetColor(math::Vector3(0.5f, 0.5f, 0.5f));
		m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsFovMin->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsFovPlus->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	}
	else if (m_camRotYActive)
	{
		m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsCamRotateY->SetColor(math::Vector3(0.5f, 0.5f, 0.5f));
		m_settingsFovMin->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsFovPlus->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	}
	else if (m_fovMinActive)
	{
		m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsFovMin->SetColor(math::Vector3(0.5f, 0.5f, 0.5f));
		m_settingsFovPlus->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
	}
	else if (m_fovPlusActive)
	{
		m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsFovMin->SetColor(math::Vector3(1.0f, 1.0f, 1.0f));
		m_settingsFovPlus->SetColor(math::Vector3(0.5f, 0.5f, 0.5f));
	}
}

void SettingsMainMenuObject::Choice()
{
	if (Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space))
	{
		if (m_camRotXActive)
		{
			if (ShipStats::s_playerStats->GetInvertCamX() == -1)
			{
				ShipStats::s_playerStats->SetInvertCamX(true);
				m_settingsCamRotateX->SetOutput("Invert Camera Rotation X (Yes)");

			}
			else
			{
				ShipStats::s_playerStats->SetInvertCamX(false);
				m_settingsCamRotateX->SetOutput("Invert Camera Rotation X (No)");

			}
		}
		else if (m_camRotYActive)
		{
			if (ShipStats::s_playerStats->GetInvertCamY() == -1)
			{
				ShipStats::s_playerStats->SetInvertCamY(true);
				m_settingsCamRotateY->SetOutput("Invert Camera Rotation Y (Yes)");

			}
			else
			{
				ShipStats::s_playerStats->SetInvertCamX(false);
				m_settingsCamRotateY->SetOutput("Invert Camera Rotation Y (No)");

			}
		}
		else if (m_fovMinActive)
		{
			if (ShipStats::s_playerStats->GetFOV() > 40)
			{
				ShipStats::s_playerStats->SetFOV(false);
				int fovInt = ShipStats::s_playerStats->GetFOV();
				m_settingsFov->SetOutput(std::to_string(fovInt));
			}
		}
		else if (m_fovPlusActive)
		{
			if (ShipStats::s_playerStats->GetFOV() < 120)
			{
				ShipStats::s_playerStats->SetFOV(true);
				int fovInt = ShipStats::s_playerStats->GetFOV();
				m_settingsFov->SetOutput(std::to_string(fovInt));
			}
		}
	}
}

void SettingsMainMenuObject::Update()
{
	CheckInput();
	SetTextActive();
	Choice();

	if(Input::GetButtonDown(Input::Buttons::BACK) || Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::B))
		Scene::LoadScene<MenuScene>();

}