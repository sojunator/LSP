#pragma once

#include <Thomas.h>
#include <string>
#include <algorithm>
#include "../scenes/MenuScene.h"
#include "../../graphics/Sprite.h"
#include "Ship.h"

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
		m_fov = 70;


		m_camera = AddComponent<component::Camera>();
		m_transform->SetPosition(0, 1, 3);
		m_music = AddComponent<component::SoundComponent>();
		m_seagull = AddComponent<component::SoundComponent>();
		m_creak = AddComponent<component::SoundComponent>();
		m_pirateMusic = AddComponent<component::SoundComponent>();
		m_text = AddComponent<component::TextComponent>();
		m_gold = AddComponent<component::TextComponent>();
		m_sprite = AddComponent<component::SpriteComponent>();
		m_backbar = AddComponent<component::SpriteComponent>();
		m_healthbar = AddComponent<component::SpriteComponent>();
		m_armbar = AddComponent<component::SpriteComponent>();
		m_healthIcon = AddComponent<component::SpriteComponent>();
		m_armIcon = AddComponent<component::SpriteComponent>();


		m_camera->SetSkybox("../res/textures/day.dds", "skyboxShader", 0);
		m_camera->AddSkybox("../res/textures/test.dds", 1);
		m_sensitivity = 2.5f;
		m_normalSpeed = 50.0f;
		m_fastSpeed = 300.0f;
		m_flySpeed = m_normalSpeed;
		m_jaw = 0;
		m_pitch = 0;

		m_seagull->SetClip("aSeagull");
		m_seagull->SetVolume(0.2);
		m_seagull->Play();

		m_creak->SetClip("fCreakLoop");
		m_creak->SetVolume(3);
		m_creak->Play();

		m_music->SetClip("aOceanAmbient");
		m_music->SetVolume(0.3);
		m_music->Play();

		m_pirateMusic->SetClip("mSeaChanty");
		m_pirateMusic->SetVolume(2);
		m_pirateMusic->Play();

		//GUI images
		m_sprite->SetName("GUI");
		m_sprite->SetPositionX(0); //Offset from top left corner
		m_sprite->SetPositionY(0);
		m_sprite->SetScale(math::Vector2(1.0f, 1.0f));
		m_sprite->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		//Background bar for health
		m_backbar->SetName("BackHealth");
		m_backbar->SetPositionX(10); //Offset from top left corner
		m_backbar->SetPositionY(960);
		m_backbar->SetScale(math::Vector2(1.0f, 1.0f));
		m_backbar->SetColor(math::Vector4(0.6f, 0.6f, 0.6f, 1.0f));

		//Healthbar
		m_healthbar->SetName("Health");
		m_healthbar->SetPositionX(14.7); //Offset from top left corner
		m_healthbar->SetPositionY(964);
		m_healthbar->SetScale(math::Vector2(1.0f, 1.0f));
		m_healthbar->SetColor(math::Vector4(0.0f, 0.7f, 0.0f, 1.0f));

		//Armorbar
		m_armbar->SetName("Armor");
		m_armbar->SetPositionX(410); //Offset from top left corner
		m_armbar->SetPositionY(964);
		m_armbar->SetScale(math::Vector2(0.0f, 1.0f));
		m_armbar->SetColor(math::Vector4(0.0f, 0.4f, 0.9f, 1.0f));

		//HealthIcon
		m_healthIcon->SetName("HealthIcon");
		m_healthIcon->SetPositionX(10.7); //Offset from top left corner
		m_healthIcon->SetPositionY(960);
		m_healthIcon->SetScale(math::Vector2(1.0f, 1.0f));
		m_healthIcon->SetColor(math::Vector4(0.0f, 0.4f, 0.9f, 1.0f));

		//ArmorIcon
		m_armIcon->SetName("ArmorIcon");
		m_armIcon->SetPositionX(409); //Offset from top left corner
		m_armIcon->SetPositionY(963);
		m_armIcon->SetScale(math::Vector2(1.0f, 1.0f));
		m_armIcon->SetColor(math::Vector4(0.0f, 0.4f, 0.9f, 1.0f));

		//Simple font
		m_text->SetFont("Name");
		m_text->SetOutput("Plunder Planets");
		m_text->SetColor(math::Vector3(0.3f, 0.15f, 0.0f));
		m_text->SetRotation(0.0f);
		m_text->SetScale(1.0f);
		m_text->SetPositionX((Window::GetWidth() / 2.f) - 210);
		m_text->SetPositionY(10);
		m_text->SetDropshadow(true);
		m_text->SetOutline(true);
		m_text->SetOrigin(false);

		//Gold font
		m_gold->SetFont("Name");
		m_gold->SetOutput("0");
		m_gold->SetColor(math::Vector3(1.0f, 0.88f, 0.0f));
		m_gold->SetRotation(0.0f);
		m_gold->SetScale(1.0f);
		m_gold->SetPositionX(250);

	/*	if (Window::GetAspectRatio() == Window::Ratio::STANDARD_169)
			m_gold->SetPositionX(Window::GetWidth() / 6.4f);
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_1610)
			m_gold->SetPositionX(Window::GetWidth() / 7.2f);
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_43)
			m_gold->SetPositionX(Window::GetWidth() / 6.5f);*/

		m_gold->SetPositionY(20);
		m_gold->SetDropshadow(true);
		m_gold->SetOutline(true);
		m_gold->SetOrigin(false);

		m_transform->SetPosition(0, 1, 3);
	};



	void Update()
	{
		m_camera->SetFar(m_far);
		m_camera->SetFov(m_fov);

		if (m_ship == nullptr)
		{
			m_ship = (Ship*)Find("Ship");
		}
		else
		{
			//To add more armor, simply do: m_ship->m_armor++ and (m_armor / m_maxArmor)



			if (m_ship->m_armor > 0)
			{
				m_armbar->SetScale(math::Vector2(m_ship->m_armor, 1.0f));
			}

			else if (m_ship->m_armor <= 0)
			{
				m_healthbar->SetScale(math::Vector2(m_ship->m_health / m_ship->m_maxHealth, 1.0f));
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
				m_transform->Translate(-m_transform->Right()*m_flySpeed*ThomasTime::GetDeltaTime());
			}
			if (Input::GetKey(Input::Keys::D))
			{
				m_transform->Translate(m_transform->Right()*m_flySpeed*ThomasTime::GetDeltaTime());
			}
			if (Input::GetKey(Input::Keys::W))
			{
				m_transform->Translate(m_transform->Forward()*m_flySpeed*ThomasTime::GetDeltaTime());
			}
			if (Input::GetKey(Input::Keys::S))
			{
				m_transform->Translate(-m_transform->Forward()*m_flySpeed*ThomasTime::GetDeltaTime());
			}
		}
		if (Input::GetMouseButton(Input::MouseButtons::RIGHT))
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_RELATIVE);
			math::Vector2 mouseDelta = Input::GetMousePosition() *m_sensitivity*ThomasTime::GetDeltaTime();

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

		
		if (Input::GetKeyDown(Input::Keys::Escape) || Input::GetButtonDown(Input::Buttons::BACK))
			Scene::LoadScene<MenuScene>();

		/*if (Input::GetKeyDown(Input::Keys::Enter) || Input::GetButtonDown(Input::Buttons::START)) //When pause scene implemented
			Scene::LoadScene<PauseScene>();*/
	}

	math::Matrix GetCameraMatrix()
	{
		return m_camera->GetViewProjMatrix();
	}

private:
	Ship* m_ship;
	component::Camera* m_camera;
	component::SoundComponent* m_seagull;
	component::SoundComponent* m_creak;
	component::SoundComponent* m_music;
	component::SoundComponent* m_pirateMusic;
	component::TextComponent* m_text;
	component::TextComponent* m_gold;
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