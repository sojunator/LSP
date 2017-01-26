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
		

		//m_renderer->SetModel("g  Mesh Mesh");

		m_cameraObject = (CameraObject*)Find("CameraObject");

		m_cameraObject->m_transform->SetPosition(math::Vector3(0, 0, 5));

		m_cameraObject->GetComponent<component::Camera>()->SetAspectRatio(16 / 9);

		return true;
	}


	void Update()
	{
		component::Camera* cam = m_cameraObject->GetComponent<component::Camera>();

		if (Input::GetKey(Input::Keys::A))
		{
			m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Right()*0.01);
		}
		if (Input::GetKey(Input::Keys::D))
		{
			m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Right()*0.01);
		}
		if (Input::GetKey(Input::Keys::W))
		{
			m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Up()*0.01);
		}
		if (Input::GetKey(Input::Keys::S))
		{
			m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Up()*0.01);
		}

		m_cameraObject->m_transform->LookAt(m_transform);

	}

private:
	CameraObject* m_cameraObject;
	component::RenderComponent* m_renderer;

};