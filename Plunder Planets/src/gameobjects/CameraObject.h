#pragma once

#include <Thomas.h>
#include <string>
#include <algorithm>
#include "Ship.h"
#include "../scenes/MenuScene.h"
#include "../../graphics/Sprite.h"

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

		m_camera = AddComponent<component::Camera>();
		m_transform->SetPosition(0, 1, 3);
		m_music = AddComponent<component::SoundComponent>();
		m_pirateMusic = AddComponent<component::SoundComponent>();
		m_text = AddComponent<component::TextComponent>();
		m_gold = AddComponent<component::TextComponent>();
		m_sprite = AddComponent<component::SpriteComponent>();
		m_healthbar = AddComponent<component::SpriteComponent>();
	

		m_camera->SetSkybox("../res/textures/cubemapTest.dds", "skyboxShader");
		m_sensitivity = 0.5f;
		m_normalSpeed = 50.0f;
		m_fastSpeed = 300.0f;
		m_flySpeed = m_normalSpeed;
		m_jaw = 0;
		m_pitch = 0;


		m_music->SetClip("aOceanAmbient");
		m_music->SetVolume(0.3);
		m_music->Play();

		m_pirateMusic->SetClip("mSeaChanty");
		m_pirateMusic->SetVolume(0.9);
		m_pirateMusic->Play();

		//GUI images
		m_sprite->SetName("GUI");
		m_sprite->SetPositionX(0); //Offset from top left corner
		m_sprite->SetPositionY(0);
		m_sprite->SetScale(math::Vector2(1.0f, 1.0f));
		m_sprite->SetColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));

		//Healthbar
		m_healthbar->SetName("Button");
		m_healthbar->SetPositionX(10); //Offset from top left corner
		m_healthbar->SetPositionY(960);
		m_healthbar->SetScale(math::Vector2(1.0f, 1.0f));
		m_healthbar->SetColor(math::Vector4(0.0f, 0.7f, 0.0f, 1.0f));


		//Simple font
		m_text->SetFont("Name");
		m_text->SetOutput("Plunder Planets");
		m_text->SetColor(math::Vector3(0.3f, 0.15f, 0.0f));
		m_text->SetRotation(0.0f);
		m_text->SetScale(1.0f);
		m_text->SetPositionX(Window::GetWidth() / 2.f);
		m_text->SetPositionY(Window::GetHeight() / 21.5f);
		m_text->SetDropshadow(true);
		m_text->SetOutline(true);

		//Gold font
		m_gold->SetFont("Name");
		m_gold->SetOutput("0");
		m_gold->SetColor(math::Vector3(1.0f, 0.88f, 0.0f));
		m_gold->SetRotation(0.0f);
		m_gold->SetScale(1.0f);

		if (Window::GetAspectRatio() == Window::Ratio::STANDARD_169)
			m_gold->SetPositionX(Window::GetWidth() / 6.4f);
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_1610)
			m_gold->SetPositionX(Window::GetWidth() / 7.2f);
		else if (Window::GetAspectRatio() == Window::Ratio::STANDARD_43)
			m_gold->SetPositionX(Window::GetWidth() / 6.5f);

		m_gold->SetPositionY(Window::GetHeight() / 21.5f);
		m_gold->SetDropshadow(true);
		m_gold->SetOutline(true);

		m_transform->SetPosition(0, 1, 3);	
	};



	void Update()
	{

		/*if (m_ship == nullptr)
		{
			m_ship = (Ship*)Find("Ship");
		}
		else
		{
			m_gold->SetOutput(std::to_string(m_ship->GetTreasure()));
		}*/
		//Healthbar code here for now
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

		if (Input::GetKey(Input::Keys::K))
		{
			if (m_healthbar->GetScale().x < 1.0f)
			{
				m_healthbar->SetScale(math::Vector2(m_healthbar->GetScale().x + 0.01f, 1.0f));
			}
		}

		if (Input::GetKey(Input::Keys::J))
		{
			if (m_healthbar->GetScale().x >= 0.0f)
			{
				m_healthbar->SetScale(math::Vector2(m_healthbar->GetScale().x - 0.01f, 1.0f));
			}
		}
		
		if (Input::GetKey(Input::Keys::A))
		{
			m_transform->Translate(-m_transform->Right()*m_flySpeed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::D))
		{
			m_transform->Translate(m_transform->Right()*m_flySpeed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::W))
		{
			m_transform->Translate(m_transform->Forward()*m_flySpeed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::S))
		{
			m_transform->Translate(-m_transform->Forward()*m_flySpeed*Time::GetDeltaTime());
		}


		if (Input::GetMouseButton(Input::MouseButtons::RIGHT))
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_RELATIVE);
			math::Vector2 mouseDelta = Input::GetMousePosition() *m_sensitivity;

			m_jaw += -mouseDelta.x*m_sensitivity*(math::PI / 180.0f);
			m_pitch += -mouseDelta.y*m_sensitivity*(math::PI / 180.0f);

			
			if (m_pitch > math::PI / 2.01f)
				m_pitch = math::PI / 2.01f;
			if (m_pitch < -math::PI / 2.01f)
				m_pitch = -math::PI/ 2.01f;

			m_transform->SetRotation(m_jaw, m_pitch, 0);
		}
		else
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_ABSOLUTE);
		}

		if (Input::GetKeyDown(Input::Keys::Escape))
			Scene::LoadScene<MenuScene>();


		if (Input::GetKey(Input::Keys::LeftShift))
		{
			m_flySpeed = m_fastSpeed;
		}
		else
			m_flySpeed = m_normalSpeed;
		
	}

	math::Matrix GetCameraMatrix() 
	{
		return m_camera->GetViewProjMatrix();
	}


private:
	Ship* m_ship;
	component::Camera* m_camera;
	component::SoundComponent* m_music;
	component::SoundComponent* m_pirateMusic;
	component::TextComponent* m_text;
	component::TextComponent* m_gold;
	component::SpriteComponent* m_sprite;
	component::SpriteComponent* m_healthbar;
	float m_sensitivity;
	float m_normalSpeed;
	float m_fastSpeed;
	float m_flySpeed;
	float m_jaw;
	float m_pitch;

};