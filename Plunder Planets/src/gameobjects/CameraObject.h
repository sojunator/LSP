#pragma once
#include <Thomas.h>
#include <string>
#include <algorithm>

using namespace thomas;
using namespace object;
class CameraObject : public GameObject
{

private:

public:
	CameraObject() : GameObject("CameraObject")
	{
		m_camera = AddComponent<component::Camera>();
		m_text = AddComponent<component::TextComponent>();
		m_sprite = AddComponent<component::SpriteComponent>();

		//GUI images
		m_sprite->SetName("GUI");
		m_sprite->SetPositionX(400.f);
		m_sprite->SetPositionY(20.f);
		m_sprite->SetScale(1.0f);

		//Text
		m_text->SetFont("Test");
		m_text->SetOutput("Plunder Planets");
		m_text->SetColor(math::Vector3(1.0f, 0.0f, 0.0f));
		m_text->SetRotation(0.0f);
		m_text->SetScale(1.5f);
		m_text->SetPositionX(400.f);
		m_text->SetPositionY(30.f);
		m_text->SetDropshadow(false);
		m_text->SetOutline(true);

		m_transform->SetPosition(0, 1, 3);
		
	};

	bool Start()
	{
		m_camera->SetSkybox("../res/textures/skymap.dds", "skyboxShader");
		m_sensitivity = 0.5f;
		m_normalSpeed = 50.0f;
		m_fastSpeed = 300.0f;
		m_flySpeed = m_normalSpeed;
		m_jaw = 0;
		m_pitch = 0;

		return true;
	}

	void Update()
	{
		
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
	component::Camera* m_camera;
	component::TextComponent* m_text;
	component::SpriteComponent* m_sprite;
	float m_sensitivity;
	float m_normalSpeed;
	float m_fastSpeed;
	float m_flySpeed;
	float m_jaw;
	float m_pitch;

};