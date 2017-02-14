#pragma once
#include <Thomas.h>
#include <string>

using namespace thomas;
using namespace object;
class MainMenuObject : public GameObject
{

private:

public:
	MainMenuObject() : GameObject("MainMenuObject")
	{
	}
	~MainMenuObject()
	{
	}

	void Start()
	{
		m_backgrounds = AddComponent<component::SpriteComponent>();
		m_camera = AddComponent<component::Camera>();
		m_startButton = AddComponent<component::SpriteComponent>();
		m_highScoreButton = AddComponent<component::SpriteComponent>();
		m_optionButton = AddComponent<component::SpriteComponent>();
		m_creditsButton = AddComponent<component::SpriteComponent>();
		m_exitButton = AddComponent<component::SpriteComponent>();
		

		m_startButton->SetName("MainMenuStart");
		m_startButton->SetPositionX(150);
		m_startButton->SetPositionY(60);
		m_startButton->SetScale(1.0f);
		m_startButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_startButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
		m_startButton->SetInteractable(true);

		m_highScoreButton->SetName("MainMenuHighScore");
		m_highScoreButton->SetPositionX(150);
		m_highScoreButton->SetPositionY(160);
		m_highScoreButton->SetScale(1.0f);
		m_highScoreButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_highScoreButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
		m_highScoreButton->SetInteractable(true);

		m_optionButton->SetName("MainMenuOptions");
		m_optionButton->SetPositionX(150);
		m_optionButton->SetPositionY(260);
		m_optionButton->SetScale(1.0f);
		m_optionButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_optionButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
		m_optionButton->SetInteractable(true);

		m_creditsButton->SetName("MainMenuCredits");
		m_creditsButton->SetPositionX(150);
		m_creditsButton->SetPositionY(350);
		m_creditsButton->SetScale(1.0f);
		m_creditsButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_creditsButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
		m_creditsButton->SetInteractable(true);

		m_exitButton->SetName("MainMenuExit");
		m_exitButton->SetPositionX(150);
		m_exitButton->SetPositionY(450);
		m_exitButton->SetScale(1.0f);
		m_exitButton->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_exitButton->SetHoverColor(math::Color(0.5, 0.5, 0.5));
		m_exitButton->SetInteractable(true);

		m_backgrounds->SetName("MainMenuBackground");
		m_backgrounds->SetPositionX(0);
		m_backgrounds->SetPositionY(0);
		m_backgrounds->SetScale(1.0f);
		m_backgrounds->SetColor(math::Color(1.0f, 1.0f, 1.0f));
		
	}


	void Update()
	{
		if (Input::GetMouseButtonDown(Input::MouseButtons::LEFT))
		{
			if (m_exitButton->isHovering())
				ThomasCore::Exit();

			if (m_startButton->isHovering())
			{
				Scene* gameScene = Scene::AddScene(new GameScene());
				Scene::LoadScene(gameScene);
				Destroy(this);
			}
		}
	}

	

private:
	component::Camera* m_camera;
	component::SpriteComponent* m_startButton;
	component::SpriteComponent* m_highScoreButton;
	component::SpriteComponent* m_optionButton;
	component::SpriteComponent* m_creditsButton;
	component::SpriteComponent* m_exitButton;
	component::SpriteComponent* m_backgrounds;

};