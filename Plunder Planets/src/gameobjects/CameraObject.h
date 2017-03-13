#pragma once

#include <Thomas.h>
#include <string>
#include <algorithm>
#include "../scenes/MenuScene.h"
#include "../../graphics/Sprite.h"
#include "Ship.h"
#include "PauseObjectMenuObject.h"

using namespace thomas;
using namespace object;
class CameraObject : public GameObject
{

private:

public:
	CameraObject() : GameObject("CameraObject")
	{

	};

	void Start()
	{
		m_far = 4000;
		m_fov = ShipStats::s_playerStats->GetFOV();


		m_camera = AddComponent<component::Camera>();
		m_transform->SetPosition(0, 1, 3);
		m_music = AddComponent<component::SoundComponent>();
		m_creak = AddComponent<component::SoundComponent>();
		m_pirateMusic = AddComponent<component::SoundComponent>();
		m_gold = AddComponent<component::TextComponent>();
		m_sprite = AddComponent<component::SpriteComponent>();
		m_backbar = AddComponent<component::SpriteComponent>();
		m_healthbar = AddComponent<component::SpriteComponent>();
		m_armbar = AddComponent<component::SpriteComponent>();
		m_healthIcon = AddComponent<component::SpriteComponent>();
		m_armIcon = AddComponent<component::SpriteComponent>();
		m_text = AddComponent<component::SpriteComponent>();
		m_levelT = AddComponent<component::TextComponent>();


		m_camera->SetSkybox("../res/textures/day.dds", "skyboxShader", 10);
		m_camera->AddSkybox("../res/textures/test.dds", 11);
		m_camera->SetSkyboxLerpValue(math::Vector3((float)rand() / ((float)RAND_MAX * 2.f), (float)rand() / ((float)RAND_MAX * 2.f), (float)rand() / ((float)RAND_MAX * 2.f)));
		m_sensitivity = 2.5f;
		m_normalSpeed = 50.0f;
		m_fastSpeed = 300.0f;
		m_flySpeed = m_normalSpeed;
		m_jaw = 0;
		m_pitch = 0;

		m_creak->SetClip("fCreakLoop");
		m_creak->SetVolume(3);
		//m_creak->Play();

		m_music->SetClip("aOceanAmbient");
		m_music->SetVolume(0.3);
		//m_music->Play();

		m_pirateMusic->SetClip("mSeaChanty");
		m_pirateMusic->SetVolume(2);
		//m_pirateMusic->Play();

		//GUI images
		m_sprite->SetName("GUI");
		m_sprite->SetPositionX(0); //Offset from top left corner
		m_sprite->SetPositionY(0);
		m_sprite->SetScale(math::Vector2(1.0f, 1.0f));
		m_sprite->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		//Background bar for health
		m_backbar->SetName("BackHealth");
		m_backbar->SetPositionX(10); //Offset from top left corner
		m_backbar->SetPositionY(1020);
		m_backbar->SetScale(math::Vector2(1.0f, 1.0f));
		m_backbar->SetColor(math::Vector4(0.6f, 0.6f, 0.6f, 1.0f));

		//Healthbar
		m_healthbar->SetName("Health");
		m_healthbar->SetPositionX(14.7); //Offset from top left corner
		m_healthbar->SetPositionY(1024);
		m_healthbar->SetScale(math::Vector2(1.0f, 1.0f));
		m_healthbar->SetColor(math::Vector4(0.0f, 0.7f, 0.0f, 1.0f));

		//Armorbar
		m_armbar->SetName("Armor");
		m_armbar->SetPositionX(410); //Offset from top left corner
		m_armbar->SetPositionY(1024);
		m_armbar->SetScale(math::Vector2(0.0f, 1.0f));
		m_armbar->SetColor(math::Vector4(0.0f, 0.4f, 0.9f, 1.0f));

		//HealthIcon
		m_healthIcon->SetName("HealthIcon");
		m_healthIcon->SetPositionX(10.7); //Offset from top left corner
		m_healthIcon->SetPositionY(1020);
		m_healthIcon->SetScale(math::Vector2(1.0f, 1.0f));
		m_healthIcon->SetColor(math::Vector4(0.0f, 0.4f, 0.9f, 1.0f));

		//ArmorIcon
		m_armIcon->SetName("ArmorIcon");
		m_armIcon->SetPositionX(409); //Offset from top left corner
		m_armIcon->SetPositionY(1023);
		m_armIcon->SetScale(math::Vector2(1.0f, 1.0f));
		m_armIcon->SetColor(math::Vector4(0.0f, 0.4f, 0.9f, 1.0f));

		//Plunder Planets text
		m_text->SetName("Plunder Planets");
		m_text->SetPositionX(Window::GetWidth() / 2.0f - 250); //Middle of screen minus half of text length in pixels (roughly)
		m_text->SetPositionY(10); //10 pixels from top

		//Level font
		m_levelT->SetFont("Pirate");
		m_levelT->SetOutput("Level " + std::to_string(ShipStats::s_currentLevel));
		m_levelT->SetColor(math::Vector3(1.0f, 0.88f, 0.0f));
		m_levelT->SetRotation(0.0f);
		m_levelT->SetScale(1.0f);
		m_levelT->SetPositionX(Window::GetWidth() - 300);
		m_levelT->SetPositionY(20);
		m_levelT->SetOutline(true);
		m_levelT->SetDropshadow(true);


		//Gold font
		m_gold->SetFont("Pirate");
		m_gold->SetOutput("0");
		m_gold->SetColor(math::Vector3(1.0f, 0.88f, 0.0f));
		m_gold->SetRotation(0.0f);
		m_gold->SetScale(1.0f);
		m_gold->SetPositionX(250);
		m_gold->SetPositionY(20);
		m_gold->SetDropshadow(true);
		m_gold->SetOutline(true);
		m_gold->SetOrigin(false);

		m_transform->SetPosition(0, 1, 3);
	};



	void Update()
	{
		m_camera->SetFar(m_far);
		m_camera->SetFov(ShipStats::s_playerStats->GetFOV());

		if (m_ship == nullptr)
		{
			m_ship = (Ship*)Find("Ship");
		}
		else if (m_pauseObj == nullptr)
			m_pauseObj = (PauseObjectMenuObject*)Find("PauseObjectMenuObject");
		else
		{
			if (m_ship->m_armor > 0)
			{
				m_armbar->SetScale(math::Vector2(m_ship->m_armor, 1.0f));
			}

			else if (m_ship->m_armor <= 0)
			{
				m_healthbar->SetScale(math::Vector2(m_ship->m_health, 1.0f));
			}
			
			m_gold->SetOutput(std::to_string(m_ship->GetTreasure()));
		}
		
		if (m_healthbar->GetScale().x > 0.6f)
		{
			m_healthbar->SetColor(math::Vector4(0.0f, 0.7f, 0.0f, 1.0f));
		}
		else if (m_healthbar->GetScale().x < 0.6f && m_healthbar->GetScale().x >= 0.3f)
		{
			m_healthbar->SetColor(math::Vector4(1.0f, 0.3f, 0.0f, 1.0f));
		}
		else if (m_healthbar->GetScale().x < 0.3f)
		{
			m_healthbar->SetColor(math::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		}

		//if (Input::GetKey(Input::Keys::K))
		//{
		//	if (m_armbar->GetScale().x < 1.0f)
		//	{
		//		m_armbar->SetScale(math::Vector2(m_armbar->GetScale().x + 0.01f, m_armbar->GetScale().y));
		//	}
		//}

		//if (Input::GetKey(Input::Keys::J))
		//{
		//	if (m_armbar->GetScale().x >= 0.0f)
		//	{
		//		m_armbar->SetScale(math::Vector2(m_armbar->GetScale().x - 0.01f, m_armbar->GetScale().y));
		//	}
		//}

		if (m_ship && m_ship->GetFreeCamera())
		{
			if (Input::GetKey(Input::Keys::A))
			{
				m_transform->Translate(-m_transform->Right()*m_flySpeed*ThomasTime::GetActualDeltaTime());
			}
			if (Input::GetKey(Input::Keys::D))
			{
				m_transform->Translate(m_transform->Right()*m_flySpeed*ThomasTime::GetActualDeltaTime());
			}
			if (Input::GetKey(Input::Keys::W))
			{
				m_transform->Translate(m_transform->Forward()*m_flySpeed*ThomasTime::GetActualDeltaTime());
			}
			if (Input::GetKey(Input::Keys::S))
			{
				m_transform->Translate(-m_transform->Forward()*m_flySpeed*ThomasTime::GetActualDeltaTime());
			}
		}
		if (Input::GetMouseButton(Input::MouseButtons::RIGHT))
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_RELATIVE);
			math::Vector2 mouseDelta = Input::GetMousePosition() *m_sensitivity*ThomasTime::GetActualDeltaTime();

			m_jaw += -mouseDelta.x*m_sensitivity*(math::PI / 180.0f);
			m_pitch += -mouseDelta.y*m_sensitivity*(math::PI / 180.0f);


			if (m_pitch > math::PI / 2.01f)
				m_pitch = math::PI / 2.01f;
			if (m_pitch < -math::PI / 2.01f)
				m_pitch = -math::PI / 2.01f;

			m_transform->SetRotation(m_jaw, m_pitch, 0);
		}
		else
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_ABSOLUTE);
		}

		if (Input::GetKey(Input::Keys::LeftShift))
		{
			m_flySpeed = m_fastSpeed;
		}
		else
			m_flySpeed = m_normalSpeed;

		
		/*if ((Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK)) && !m_pauseObj->GetPauseState())
			Scene::LoadScene<MenuScene>();*/

		/*if (Input::GetKeyDown(Input::Keys::Enter) || Input::GetButtonDown(Input::Buttons::START)) //When pause scene implemented
			Scene::LoadScene<PauseScene>();*/
	}

	math::Matrix GetCameraMatrix()
	{
		return m_camera->GetViewProjMatrix();
	}

private:
	Ship* m_ship;
	PauseObjectMenuObject* m_pauseObj;
	component::Camera* m_camera;
	component::SoundComponent* m_seagull;
	component::SoundComponent* m_creak;
	component::SoundComponent* m_music;
	component::SoundComponent* m_pirateMusic;
	component::TextComponent* m_gold;
	component::TextComponent* m_levelT;
	component::SpriteComponent* m_text;
	component::SpriteComponent* m_sprite;
	component::SpriteComponent* m_healthbar;
	component::SpriteComponent* m_backbar;
	component::SpriteComponent* m_armbar;
	component::SpriteComponent* m_healthIcon;
	component::SpriteComponent* m_armIcon;
	float m_sensitivity;
	float m_normalSpeed;
	float m_fastSpeed;
	float m_flySpeed;
	float m_jaw;
	float m_pitch;
	float m_far;
	float m_fov;
};