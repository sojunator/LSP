#pragma once
#pragma once
#include <Thomas.h>
#include "PauseObjectMenuObject.h"
#include "ShipStats.h"

using namespace thomas;
using namespace object;
class SettingsMenuObject : public GameObject
{

private:

public:
	SettingsMenuObject() : GameObject("SettingsMenuObject")
	{

	}
	~SettingsMenuObject()
	{
	}

	void Start()
	{
		m_firstTimeHax = false;
		m_settingsHeadLine = AddComponent<component::TextComponent>();
		m_settingsCamRotateX = AddComponent<component::TextComponent>();
		m_settingsCamRotateY = AddComponent<component::TextComponent>();
		m_settingsFovMin = AddComponent<component::TextComponent>();
		m_settingsFovPlus = AddComponent<component::TextComponent>();
		m_settingsFov = AddComponent<component::TextComponent>();
		m_pauseObj = (PauseObjectMenuObject*)Find("PauseObjectMenuObject");

		InitMenu();
	}

	void InitMenu()
	{
		m_settingsHeadLine->SetFont("SafeToLeave");
		m_settingsHeadLine->SetOutput("Settings");
		m_settingsHeadLine->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_settingsHeadLine->SetRotation(0.0f);
		m_settingsHeadLine->SetScale(2.0f);
		m_settingsHeadLine->SetPositionX((Window::GetWidth() / 4) * 2);
		m_settingsHeadLine->SetPositionY(Window::GetHeight() / 4.5);
		m_settingsHeadLine->SetDropshadow(true);
		m_settingsHeadLine->SetOutline(true);
		m_settingsHeadLine->SetOrigin(false);

		m_settingsCamRotateX->SetFont("SafeToLeave");
		if(ShipStats::s_playerStats->GetInvertCamX() == -1)
			m_settingsCamRotateX->SetOutput("Invert Camera Rotation X (No)");
		else
			m_settingsCamRotateX->SetOutput("Invert Camera Rotation X (Yes)");
		m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_settingsCamRotateX->SetRotation(0.0f);
		m_settingsCamRotateX->SetScale(1.0f);
		m_settingsCamRotateX->SetPositionX((Window::GetWidth() / 4) * 2);
		m_settingsCamRotateX->SetPositionY(Window::GetHeight() / 4 + 100);
		m_settingsCamRotateX->SetDropshadow(true);
		m_settingsCamRotateX->SetOutline(true);
		m_settingsCamRotateX->SetOrigin(false);

		m_settingsCamRotateY->SetFont("SafeToLeave");
		if (ShipStats::s_playerStats->GetInvertCamY() == -1)
			m_settingsCamRotateY->SetOutput("Invert Camera Rotation Y (No)");
		else
			m_settingsCamRotateY->SetOutput("Invert Camera Rotation Y (Yes)");
		m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_settingsCamRotateY->SetRotation(0.0f);
		m_settingsCamRotateY->SetScale(1.0f);
		m_settingsCamRotateY->SetPositionX((Window::GetWidth() / 4) * 2);
		m_settingsCamRotateY->SetPositionY(Window::GetHeight() / 4 + 200);
		m_settingsCamRotateY->SetDropshadow(true);
		m_settingsCamRotateY->SetOutline(true);
		m_settingsCamRotateY->SetOrigin(false);

		m_settingsFovMin->SetFont("SafeToLeave");
		m_settingsFovMin->SetOutput("FOV-");
		m_settingsFovMin->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_settingsFovMin->SetRotation(0.0f);
		m_settingsFovMin->SetScale(1.0f);
		m_settingsFovMin->SetPositionX((Window::GetWidth() / 4) * 2);
		m_settingsFovMin->SetPositionY(Window::GetHeight() / 4 + 300);
		m_settingsFovMin->SetDropshadow(true);
		m_settingsFovMin->SetOutline(true);
		m_settingsFovMin->SetOrigin(false);

		m_settingsFovPlus->SetFont("SafeToLeave");
		m_settingsFovPlus->SetOutput("FOV+");
		m_settingsFovPlus->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_settingsFovPlus->SetRotation(0.0f);
		m_settingsFovPlus->SetScale(1.0f);
		m_settingsFovPlus->SetPositionX((Window::GetWidth() / 4) * 2 + 300);
		m_settingsFovPlus->SetPositionY(Window::GetHeight() / 4 + 300);
		m_settingsFovPlus->SetDropshadow(true);
		m_settingsFovPlus->SetOutline(true);
		m_settingsFovPlus->SetOrigin(false);

		int fovInt = ShipStats::s_playerStats->GetFOV();
		m_settingsFov->SetFont("SafeToLeave");
		m_settingsFov->SetOutput(std::to_string(fovInt));
		m_settingsFov->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_settingsFov->SetRotation(0.0f);
		m_settingsFov->SetScale(1.0f);
		m_settingsFov->SetPositionX((Window::GetWidth() / 4) * 2 + 175);
		m_settingsFov->SetPositionY(Window::GetHeight() / 4 + 300);
		m_settingsFov->SetDropshadow(true);
		m_settingsFov->SetOutline(true);
		m_settingsFov->SetOrigin(false);

		m_camRotXActive = true;
		m_camRotYActive = false;
		m_fovMinActive = false;
		m_fovPlusActive = false;

		m_inputDelay = 0.0f; // so that we don't do 500 inputs per second.
		HideMenu();
	}

	void DisplayMenu()
	{
		m_settingsHeadLine->SetActive(true);
		m_settingsCamRotateX->SetActive(true);
		m_settingsCamRotateY->SetActive(true);
		m_settingsFovMin->SetActive(true);
		m_settingsFovPlus->SetActive(true);
		m_settingsFov->SetActive(true);
	}

	void HideMenu()
	{
		m_settingsHeadLine->SetActive(false);
		m_settingsCamRotateX->SetActive(false);
		m_settingsCamRotateY->SetActive(false);
		m_settingsFovMin->SetActive(false);
		m_settingsFovPlus->SetActive(false);
		m_settingsFov->SetActive(false);
	}

	void CheckState()
	{
		if (m_pauseObj->GetSettingsState())
		{
			DisplayMenu();
			if (Input::GetButtonDown(Input::Buttons::START) || Input::GetKeyDown(Input::Keys::Enter))
			{
				m_pauseObj->SetSettingsState(false);
				HideMenu();
			}
		}
		else
		{
			HideMenu();
		}
		
	}

	void CheckInput()
	{
		if (m_inputDelay < 0.001f)
		{
			if (m_pauseObj->GetSettingsState())
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
		}
		else
		{
			m_inputDelay -= thomas::ThomasTime::GetActualDeltaTime();
		}
	}

	void SetTextActive()
	{
		if (m_camRotXActive)
		{
			m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
			m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsFovMin->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsFovPlus->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		}
		else if(m_camRotYActive)
		{
			m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
			m_settingsFovMin->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsFovPlus->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		}
		else if (m_fovMinActive)
		{
			m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsFovMin->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
			m_settingsFovPlus->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		}
		else if (m_fovPlusActive)
		{
			m_settingsCamRotateX->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsCamRotateY->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsFovMin->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_settingsFovPlus->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
		}
	}

	void Choice()
	{
		if ((Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space)) && m_pauseObj->GetSettingsState())
		{
			if (!m_firstTimeHax) //Because same action that opened settings menu also triggers an action in settingsmenu
				m_firstTimeHax = true;
			else if (m_camRotXActive)
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
		if (Input::GetButtonDown(Input::Buttons::B) || Input::GetKeyDown(Input::Keys::Back))
		{
			m_pauseObj->SetSettingsState(false);
			m_firstTimeHax = false;
			HideMenu();
		}
	}

	void Update()
	{
		CheckState();
		CheckInput();

		if (m_pauseObj->GetSettingsState())
		{
			SetTextActive();
			Choice();
		}
	};

private:
	float m_inputDelay;
	bool m_firstTimeHax;
	bool m_camRotXActive;
	bool m_camRotYActive;
	bool m_fovMinActive;
	bool m_fovPlusActive;

	PauseObjectMenuObject* m_pauseObj;
	component::TextComponent* m_settingsHeadLine;
	component::TextComponent* m_settingsCamRotateX;
	component::TextComponent* m_settingsCamRotateY;
	component::TextComponent* m_settingsFovMin;
	component::TextComponent* m_settingsFovPlus;
	component::TextComponent* m_settingsFov;
};
