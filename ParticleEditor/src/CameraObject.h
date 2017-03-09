#pragma once

#include <Thomas.h>

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
		m_transform->SetPosition(0, 90, 200);
		m_transform->LookAt(math::Vector3(0, 0, 0));
		m_camera->SetFar(1000);
		m_camera->SetFov(70);
		m_sensitivity = 2.5f;
		m_distance = 200;

	};



	void Update()
	{
	
		if (Input::GetMouseButton(Input::MouseButtons::RIGHT))
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_RELATIVE);
			math::Vector2 mouseDelta = Input::GetMousePosition() *m_sensitivity*ThomasTime::GetDeltaTime();



			m_transform->SetPosition(0, 0, 0);

			m_transform->RotateByAxis(math::Vector3::Up, mouseDelta.x);
			m_transform->Translate(-m_transform->Forward() * m_distance);
			//m_transform->LookAt(math::Vector3(0,0,0));
			//m_transform->RotateByAxis(math::Vector3::Right, mouseDelta.y);
		}
		else
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_ABSOLUTE);
		}

		if (Input::GetKeyDown(Input::Keys::Escape))
			ThomasCore::Exit();
	}

	math::Matrix GetCameraMatrix()
	{
		return m_camera->GetViewProjMatrix();
	}

private:
	float m_distance;
	float m_sensitivity;
	component::Camera* m_camera;
};