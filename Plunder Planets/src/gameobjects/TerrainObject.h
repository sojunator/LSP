#pragma once
#pragma once
#include <Thomas.h>
#include <string>

#include "CameraObject.h"

using namespace thomas;
using namespace object;
class TerrainObject : public GameObject
{

private:

public:
	TerrainObject() : GameObject("TerrainObject")
	{
		m_renderer = AddComponent<component::RenderComponent>();

	}

	bool Start()
	{


		m_renderer->SetModel("Plane-1");

		m_cameraObject = Find("CameraObject");

		/*m_cameraObject->m_transform->SetPosition(math::Vector3(0, 0, 50));*/
		m_transform->SetPosition(math::Vector3(0, 0, -20));


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

			m_cameraObject->m_transform->LookAt(m_transform);

	}

private:
	component::RenderComponent* m_renderer;
	object::GameObject* m_cameraObject;

};