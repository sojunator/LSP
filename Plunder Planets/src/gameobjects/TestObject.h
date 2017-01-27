#pragma once
#include <Thomas.h>
#include <string>

#include "CameraObject.h"

using namespace thomas;
using namespace object;
class TestObject : public GameObject
{

private:

public:
	TestObject() : GameObject("TestObject") 
	{
		m_renderer = AddComponent<component::RenderComponent>();

	}

	bool Start()
	{
		

		m_renderer->SetModel("testModel");
		
		m_cameraObject = Find("CameraObject");

		//m_cameraObject->m_transform->SetPosition(math::Vector3(0, 0, 50));
		m_transform->SetPosition(math::Vector3(0, 0, -5));
		m_cameraObject->GetComponent<component::Camera>()->SetAspectRatio(16 / 9);


		return true;
	}


	void Update()
	{
		component::Camera* cam = m_cameraObject->GetComponent<component::Camera>();

		float speed = 10;
		if (Input::GetKey(Input::Keys::A))
		{
			m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Right()*speed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::D))
		{
			m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Right()*speed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::W))
		{
			m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Up()*speed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::S))
		{
			m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Up()*speed*Time::GetDeltaTime());
		}

		m_cameraObject->m_transform->LookAt(m_transform);

	}

private:
	component::RenderComponent* m_renderer;
	object::GameObject* m_cameraObject;

};