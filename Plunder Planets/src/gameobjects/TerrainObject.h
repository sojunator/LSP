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

	}

private:
	component::RenderComponent* m_renderer;
	object::GameObject* m_cameraObject;

};