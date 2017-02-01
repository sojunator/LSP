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
		m_light = AddComponent<component::PointLight>();
		m_lightTheSecond = AddComponent<component::DirectionalLight>();
		
	}

	bool Start()
	{
		

		m_renderer->SetModel("testModel");
		
		m_cameraObject = Find("CameraObject");

		m_lightTheSecond->SetDirection(thomas::math::Vector4(-1, 0, 1, 0));
		m_lightTheSecond->SetDiffuseColor(thomas::math::Vector4(0, 0, 0.25, 1));
		
		
		//m_cameraObject->m_transform->SetPosition(math::Vector3(0, 0, 50));
		m_transform->SetPosition(math::Vector3(0, -3, -10));


		return true;
	}


	void Update()
	{
		component::Camera* cam = m_cameraObject->GetComponent<component::Camera>();
		
		

		float speed = 10;
		if (Input::GetKey(Input::Keys::A))
		{
			m_transform->Rotate(-speed*Time::GetDeltaTime(), 0, 0);
		}
		if (Input::GetKey(Input::Keys::D))
		{
			m_transform->Rotate(speed*Time::GetDeltaTime(), 0, 0);
		}
		if (Input::GetKey(Input::Keys::W))
		{
			m_transform->Rotate(0, -speed*Time::GetDeltaTime(), 0);
		}
		if (Input::GetKey(Input::Keys::S))
		{
			m_transform->Rotate(0, speed*Time::GetDeltaTime(), 0);
		}

	//	m_cameraObject->m_transform->LookAt(m_transform);

	}

private:
	component::RenderComponent* m_renderer;
	GameObject* m_cameraObject;
	component::Light* m_light;
	component::DirectionalLight* m_lightTheSecond;

};