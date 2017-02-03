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
		m_music = AddComponent<component::SoundComponent>();
		m_ambient = AddComponent<component::SoundComponent>();
		m_effect = AddComponent<component::SoundComponent>();
		m_light = AddComponent<component::PointLight>();
		m_lightTheSecond = AddComponent<component::DirectionalLight>();
		
	}

	bool Start()
	{
		

		m_renderer->SetModel("testModel");
		
		m_cameraObject = Find("CameraObject");

		m_lightTheSecond->SetDirection(thomas::math::Vector4(0, 0, -1, 0));
		//m_lightTheSecond->SetDiffuseColor(thomas::math::Vector4(0, 0, 0.25, 1));
		
		
		m_music->SetName("mThomas");
		m_music->SetVolume(0.5f);
		m_ambient->SetName("aWindLong");
		m_ambient->SetVolume(5.0f);
		m_effect->SetName("fCannon1");
		m_effect->SetVolume(5.0f);
		m_music->Play();
		m_ambient->Play();

		//m_cameraObject->m_transform->SetPosition(math::Vector3(0, 0, 50));
		m_transform->SetPosition(math::Vector3(0, -3, -10));


		return true;
	}


	void Update()
	{
		if (Input::GetKeyDown(Input::Keys::P))
			m_effect->Play();
	}

private:
	component::RenderComponent* m_renderer;
	component::Light* m_light;
	component::DirectionalLight* m_lightTheSecond;
	object::GameObject* m_cameraObject;
	component::SoundComponent* m_music;
	component::SoundComponent* m_ambient;
	component::SoundComponent* m_effect;

};