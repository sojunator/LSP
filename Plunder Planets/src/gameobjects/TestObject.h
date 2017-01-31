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
		m_transform->SetPosition(math::Vector3(0, -3, -10));


		return true;
	}


	void Update()
	{


	}

private:
	component::RenderComponent* m_renderer;
	object::GameObject* m_cameraObject;

};