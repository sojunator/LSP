#pragma once
#pragma once
#include <Thomas.h>
#include "PauseObjectMenuObject.h"

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
		m_settingsActive = false;
		m_settingsHeadLine = AddComponent<component::TextComponent>();
		/*m_pauseQuit = AddComponent<component::TextComponent>();
		m_pauseResume = AddComponent<component::TextComponent>();*/
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

		/*m_pauseResume->SetFont("SafeToLeave");
		m_pauseResume->SetOutput("Resume");
		m_pauseResume->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_pauseResume->SetRotation(0.0f);
		m_pauseResume->SetScale(1.0f);
		m_pauseResume->SetPositionX(Window::GetWidth() / 4);
		m_pauseResume->SetPositionY(Window::GetHeight() / 4 + 100);
		m_pauseResume->SetDropshadow(true);
		m_pauseResume->SetOutline(true);
		m_pauseResume->SetOrigin(false);

		m_pauseQuit->SetFont("SafeToLeave");
		m_pauseQuit->SetOutput("Quit");
		m_pauseQuit->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_pauseQuit->SetRotation(0.0f);
		m_pauseQuit->SetScale(1.0f);
		m_pauseQuit->SetPositionX(Window::GetWidth() / 4);
		m_pauseQuit->SetPositionY(Window::GetHeight() / 4 + 200);
		m_pauseQuit->SetDropshadow(true);
		m_pauseQuit->SetOutline(true);
		m_pauseQuit->SetOrigin(false);

		m_resumeActive = true;
		m_quitActive = false;*/

		//m_inputDelay = 0.0f; // so that we don't do 500 inputs per second.
		HideMenu();
	}

	void DisplayMenu()
	{
		m_settingsHeadLine->SetActive(true);
		/*
		m_pauseQuit->SetActive(true);
		m_pauseResume->SetActive(true);*/
	}

	void HideMenu()
	{
		m_settingsHeadLine->SetActive(false);
		/*m_pauseQuit->SetActive(false);
		m_pauseResume->SetActive(false);*/
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
	{/*
		if (m_inputDelay < 0.001f)
		{
			if (m_isPaused)
			{
				if (Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetLeftStickY() > 0.0f || Input::GetKey(Input::Keys::Down))
				{
					if (m_resumeActive)
					{
						m_quitActive = true;
						m_resumeActive = false;
					}
					else
					{
						m_resumeActive = true;
						m_quitActive = false;
					}

					m_inputDelay = 0.3f;
				}

				if (Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetLeftStickY() < 0.0f || Input::GetKey(Input::Keys::Up))
				{
					if (m_resumeActive)
					{
						m_quitActive = true;
						m_resumeActive = false;
					}
					else
					{
						m_resumeActive = true;
						m_quitActive = false;
					}

					m_inputDelay = 0.3f;
				}
			}*/
		/*}
		else
		{
			m_inputDelay -= thomas::ThomasTime::GetActualDeltaTime();
		}*/
	}

	void SetTextActive()
	{
		/*if (m_resumeActive)
		{
			m_pauseResume->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
			m_pauseQuit->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		}
		else
		{
			m_pauseResume->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_pauseQuit->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
		}*/
	}

	void Choice()
	{
		if (Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space)) //FIX IF PRESS B, m_pauseObj->SetSettingsState(false)
		{
			/*if (m_quitActive)
			{
				thomas::Scene::UnloadScene();
				Scene::LoadScene<MenuScene>();
			}

			if (m_resumeActive)
			{
				m_isPaused = false;
				HideMenu();
			}*/
		}
		if (Input::GetButtonDown(Input::Buttons::B) || Input::GetKeyDown(Input::Keys::OemBackslash))
		{
			m_pauseObj->SetSettingsState(false);
			HideMenu();
		}
	}

	void Update()
	{
		CheckState();
		/*CheckInput();*/

		if (m_pauseObj->GetSettingsState())
		{
			//SetTextActive();
			Choice();
		}
	};

private:
	//float m_inputDelay;
	bool m_settingsActive;
	//bool m_resumeActive;
	//bool m_quitActive;
	PauseObjectMenuObject* m_pauseObj;
	component::TextComponent* m_settingsHeadLine;
	//component::TextComponent* m_pauseQuit;
	//component::TextComponent* m_pauseResume;
};
