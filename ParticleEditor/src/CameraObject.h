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
		m_transform->LookAt(math::Vector3(0, 20, 0));
		m_camera->SetFar(1000);
		m_camera->SetFov(70);
		m_sensitivity = 2.5f;
		m_distance = 200;
		m_minDistance = 10;
		m_maxDistance = 500;
		m_scrollSpeed = 10;
	};



	void Update()
	{
	
		if (Input::GetMouseButton(Input::MouseButtons::RIGHT))
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_RELATIVE);
			math::Vector2 mouseDelta = Input::GetMousePosition() *m_sensitivity*ThomasTime::GetDeltaTime();

			m_transform->SetPosition(0, 20, 0);

			m_transform->RotateByAxis(math::Vector3::Up, mouseDelta.x);
			
			//m_transform->LookAt(math::Vector3(0,0,0));
			//m_transform->RotateByAxis(math::Vector3::Right, mouseDelta.y);
		}
		else
		{
			Input::SetMouseMode(Input::MouseMode::POSITION_ABSOLUTE);
		}

		m_distance = (-Input::GetMouseScroll()/120)*m_scrollSpeed + 200;

		m_distance = max(m_minDistance, min(m_distance, m_maxDistance));

		m_transform->SetPosition(-m_transform->Forward() * m_distance);
		m_transform->Translate(0, 20, 0);
		if (Input::GetKeyDown(Input::Keys::Escape))
			ThomasCore::Exit();
	}

	math::Matrix GetCameraMatrix()
	{
		return m_camera->GetViewProjMatrix();
	}

private:
	float m_minDistance;
	float m_maxDistance;
	float m_scrollSpeed;
	float m_distance;
	float m_sensitivity;
	component::Camera* m_camera;
};