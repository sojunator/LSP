#pragma once
#include <Thomas.h>
#include <string>

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
		return true;
	}

	math::Matrix GetCameraMatrix() 
	{
		return m_camera->GetViewProjMatrix();
	}


private:
	component::Camera* m_camera;

};