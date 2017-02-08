#pragma once
#include <Thomas.h>
#include <string>
#include <algorithm>
#include "Ship.h"

using namespace thomas;
using namespace object;
class CameraObject : public GameObject
{

private:

public:
	CameraObject() : GameObject("CameraObject")
	{
		m_camera = AddComponent<component::Camera>();
		m_transform->SetPosition(0, 1, 3);
		m_music = AddComponent<component::SoundComponent>();
		m_pirateMusic = AddComponent<component::SoundComponent>();
		m_text = AddComponent<component::TextComponent>();
		m_gold = AddComponent<component::TextComponent>();
		m_sprite = AddComponent<component::SpriteComponent>();
		m_chest = AddComponent<component::SpriteComponent>();
	
		//GUI images
		m_sprite->SetName("GUI");	
		m_sprite->SetPositionX(400);
		m_sprite->SetPositionY(270);
		m_sprite->SetScale(1.0f);

		m_chest->SetName("Chest");
		m_chest->SetPositionX(120);
		m_chest->SetPositionY(30);
		m_chest->SetScale(0.09f);

		//Simple font
		m_text->SetFont("Name");
		m_text->SetOutput("Plunder Planets");
		m_text->SetColor(math::Vector3(0.3f, 0.15f, 0.0f));
		m_text->SetRotation(0.0f);
		m_text->SetScale(1.0f);
		m_text->SetPositionX(960.f);
		m_text->SetPositionY(30.f);
		m_text->SetDropshadow(true);
		m_text->SetOutline(true);

		//Gold font
		m_gold->SetFont("Gold");
		m_gold->SetOutput("0");
		m_gold->SetColor(math::Vector3(0.3f, 0.15f, 0.0f));
		m_gold->SetRotation(0.0f);
		m_gold->SetScale(1.0f);
		m_gold->SetPositionX(300.f);
		m_gold->SetPositionY(30.f);
		m_gold->SetDropshadow(true);
		m_gold->SetOutline(true);

		m_transform->SetPosition(0, 1, 3);	
	};

	bool Start()
	{
		//m_ship = (Ship*)Find("Ship");
		m_camera->SetSkybox("../res/textures/skymap.dds", "skyboxShader");
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
		
		return true;
	}

	void Update()
	{
		//m_gold->SetOutput(std::to_string(m_ship->GetTreasure()));
		
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
	//Ship* m_ship;
	component::Camera* m_camera;
	component::SoundComponent* m_music;
	component::SoundComponent* m_pirateMusic;
	component::TextComponent* m_text;
	component::TextComponent* m_gold;
	component::SpriteComponent* m_sprite;
	component::SpriteComponent* m_chest;
	float m_sensitivity;
	float m_normalSpeed;
	float m_fastSpeed;
	float m_flySpeed;
	float m_jaw;
	float m_pitch;

};