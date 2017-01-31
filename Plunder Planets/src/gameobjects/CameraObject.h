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
		m_camera->SetSkybox("../res/textures/test.dds", "skyboxShader");
		return true;
	}

	void Update()
	{
	}

	math::Matrix GetCameraMatrix() 
	{
		return m_camera->GetViewProjMatrix();
	}


private:
	component::Camera* m_camera;

};