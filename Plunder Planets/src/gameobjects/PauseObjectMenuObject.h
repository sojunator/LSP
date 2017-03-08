#pragma once
#include <Thomas.h>

using namespace thomas;
using namespace object;
class PauseObjectMenuObject : public GameObject
{

private:

public:
	PauseObjectMenuObject() : GameObject("PauseObjectMenuObject")
	{

	}
	~PauseObjectMenuObject()
	{
	}

	void Start()
	{
		m_isPaused = false;
		m_pauseHeadLine = AddComponent<component::TextComponent>();
		m_pauseResume = AddComponent<component::TextComponent>();
		m_pauseSettings = AddComponent<component::TextComponent>();
		m_pauseQuit = AddComponent<component::TextComponent>();
		

		InitMenu();
	}

	void InitMenu()
	{
		m_pauseHeadLine->SetFont("SafeToLeave");
		m_pauseHeadLine->SetOutput("Paused");
		m_pauseHeadLine->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_pauseHeadLine->SetRotation(0.0f);
		m_pauseHeadLine->SetScale(2.0f);
		m_pauseHeadLine->SetPositionX(Window::GetWidth() / 4);
		m_pauseHeadLine->SetPositionY(Window::GetHeight() / 4.5);
		m_pauseHeadLine->SetDropshadow(true);
		m_pauseHeadLine->SetOutline(true);
		m_pauseHeadLine->SetOrigin(false);

		m_pauseResume->SetFont("SafeToLeave");
		m_pauseResume->SetOutput("Resume");
		m_pauseResume->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_pauseResume->SetRotation(0.0f);
		m_pauseResume->SetScale(1.0f);
		m_pauseResume->SetPositionX(Window::GetWidth() / 4);
		m_pauseResume->SetPositionY(Window::GetHeight() / 4 + 100);
		m_pauseResume->SetDropshadow(true);
		m_pauseResume->SetOutline(true);
		m_pauseResume->SetOrigin(false);

		m_pauseSettings->SetFont("SafeToLeave");
		m_pauseSettings->SetOutput("Settings");
		m_pauseSettings->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_pauseSettings->SetRotation(0.0f);
		m_pauseSettings->SetScale(1.0f);
		m_pauseSettings->SetPositionX(Window::GetWidth() / 4);
		m_pauseSettings->SetPositionY(Window::GetHeight() / 4 + 200);
		m_pauseSettings->SetDropshadow(true);
		m_pauseSettings->SetOutline(true);
		m_pauseSettings->SetOrigin(false);

		m_pauseQuit->SetFont("SafeToLeave");
		m_pauseQuit->SetOutput("Quit");
		m_pauseQuit->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_pauseQuit->SetRotation(0.0f);
		m_pauseQuit->SetScale(1.0f);
		m_pauseQuit->SetPositionX(Window::GetWidth() / 4);
		m_pauseQuit->SetPositionY(Window::GetHeight() / 4 + 300 );
		m_pauseQuit->SetDropshadow(true);
		m_pauseQuit->SetOutline(true);
		m_pauseQuit->SetOrigin(false);

		m_resumeActive = true;
		m_quitActive = false;
		
		m_inputDelay = 0.0f; // so that we don't do 500 inputs per second.
		HideMenu();
	}

	void DisplayMenu()
	{
		m_pauseHeadLine->SetActive(true);
		m_pauseResume->SetActive(true);
		m_pauseSettings->SetActive(true);
		m_pauseQuit->SetActive(true);
		
	}

	void HideMenu()
	{
		m_pauseHeadLine->SetActive(false); 		
		m_pauseResume->SetActive(false);
		m_pauseSettings->SetActive(false);
		m_pauseQuit->SetActive(false);
	}

	void CheckState()
	{
		if (Input::GetButtonDown(Input::Buttons::START) || Input::GetKeyDown(Input::Keys::Enter))
		{
			
			if (m_isPaused)
			{	
				HideMenu();
				m_isPaused = false;
			}
			else
			{
				DisplayMenu();
				m_isPaused = true;
			}
		}
	}

	void CheckInput()
	{
		if (m_inputDelay < 0.001f)
		{
			if (m_isPaused)
			{
				if (Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetLeftStickY() < 0.0f || Input::GetKey(Input::Keys::Down))
				{
					if (m_resumeActive)
					{
						m_resumeActive = false;
						m_settingsActive = true;
						m_quitActive = false;
					}
					else if (m_settingsActive)
					{
						m_resumeActive = false;
						m_settingsActive = false;
						m_quitActive = true;
					}
					else if(m_quitActive)
					{
						m_resumeActive = true;
						m_settingsActive = false;
						m_quitActive = false;
					}

					m_inputDelay = 0.3f;
				}

				if (Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetLeftStickY() > 0.0f || Input::GetKey(Input::Keys::Up))
				{
					if (m_resumeActive)
					{
						m_resumeActive = false;
						m_settingsActive = false;
						m_quitActive = true;
						
					}
					else if (m_settingsActive)
					{
						m_resumeActive = true;
						m_settingsActive = false;
						m_quitActive = false;
					}
					else if (m_quitActive)
					{
						m_resumeActive = false;
						m_settingsActive = true;
						m_quitActive = false;
					}

					m_inputDelay = 0.3f;
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
		if (m_resumeActive)
		{
			m_pauseResume->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
			m_pauseSettings->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_pauseQuit->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		}
		else if(m_settingsActive)
		{
			m_pauseResume->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_pauseSettings->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
			m_pauseQuit->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		}
		else if(m_quitActive)
		{
			m_pauseResume->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_pauseSettings->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_pauseQuit->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
		}
	}

	void Choice()
	{
		if (Input::GetButtonDown(Input::Buttons::A) || Input::GetKeyDown(Input::Keys::Space))
		{
			if (m_quitActive)
			{
				thomas::Scene::UnloadScene();
				Scene::LoadScene<MenuScene>();
			}

			if (m_resumeActive)
			{
				m_isPaused = false;
				HideMenu();
			}

			if (m_settingsActive)
			{
				//soon^tm
			}
		}
	}

	void Update()
	{
		CheckState();
		CheckInput();

		if (m_isPaused)
		{
			SetTextActive();
			Choice();
		}
	};

	void LateUpdate()
	{
		if (m_isPaused)
		{
			ThomasTime::SetTimescale(0.0f);
		}
		else
		{
			ThomasTime::SetTimescale(1.0f);
		}
	}

	bool GetSettingsActive()
	{
		return m_settingsActive;
	}


private:
	float m_inputDelay;
	bool m_isPaused;
	bool m_resumeActive;
	bool m_settingsActive;
	bool m_quitActive;
	component::TextComponent* m_pauseHeadLine;
	component::TextComponent* m_pauseResume;
	component::TextComponent* m_pauseSettings;
	component::TextComponent* m_pauseQuit;
	
};
