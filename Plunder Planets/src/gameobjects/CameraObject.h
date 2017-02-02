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
	};

	bool Start()
	{

		m_camera->SetSkybox("../res/textures/test.dds", "skyboxShader");
		m_camera->SetGUI("../res/dearleader.jpg", "GUIShader", Window::GetWidth(), 100);
		m_sensitivity = 0.5f;
		m_normalSpeed = 10.0f;
		m_fastSpeed = 30.0f;
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
	float m_sensitivity;
	float m_normalSpeed;
	float m_fastSpeed;
	float m_flySpeed;
	float m_jaw;
	float m_pitch;

};