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
		m_pauseQuit = AddComponent<component::TextComponent>();
		m_pauseResume = AddComponent<component::TextComponent>();

		InitMenu();
	}

	void InitMenu()
	{
		m_pauseHeadLine->SetFont("SafeToLeave");
		m_pauseHeadLine->SetOutput("Paused");
		m_pauseHeadLine->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_pauseHeadLine->SetRotation(0.0f);
		m_pauseHeadLine->SetScale(1.0f);
		m_pauseHeadLine->SetPositionX(Window::GetWidth() / 4);
		m_pauseHeadLine->SetPositionY(Window::GetHeight() / 4);
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

		m_pauseQuit->SetFont("SafeToLeave");
		m_pauseQuit->SetOutput("Quit");
		m_pauseQuit->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		m_pauseQuit->SetRotation(0.0f);
		m_pauseQuit->SetScale(1.0f);
		m_pauseQuit->SetPositionX(Window::GetWidth() / 4);
		m_pauseQuit->SetPositionY(Window::GetHeight() / 4 + 200 );
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
		m_pauseQuit->SetActive(true);
		m_pauseResume->SetActive(true);
	}

	void HideMenu()
	{
		m_pauseHeadLine->SetActive(false); 
		m_pauseQuit->SetActive(false);
		m_pauseResume->SetActive(false);
	}

	void CheckState()
	{
		if (Input::GetButtonDown(Input::Buttons::START))
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
				if (Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetLeftStickY() > 0.0f)
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

				if (Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetLeftStickY() < 0.0f)
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
			m_pauseQuit->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
		}
		else
		{
			m_pauseResume->SetColor(math::Vector3(1.0f, 1.0f, 0.0f));
			m_pauseQuit->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
		}
	}

	void Choice()
	{
		if (Input::GetButtonDown(Input::Buttons::A))
		{
			if (m_quitActive)
			{
				thomas::Scene::UnloadScene();
				Scene::LoadScene<UpgradeScene>();
			}

			if (m_resumeActive)
			{
				m_isPaused = false;
				HideMenu();
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


private:
	float m_inputDelay;
	bool m_isPaused;
	bool m_resumeActive;
	bool m_quitActive;
	component::TextComponent* m_pauseHeadLine;
	component::TextComponent* m_pauseQuit;
	component::TextComponent* m_pauseResume;
};
