#pragma once
#include <Thomas.h>
#include <string>



using namespace thomas;
using namespace object;
class Ship : public GameObject
{

private:

public:
	Ship() : GameObject("Ship")
	{
		m_renderer = AddComponent<component::RenderComponent>();
		m_sound = AddComponent<component::SoundComponent>();

	}

	bool Start()
	{
		m_renderer->SetModel("testModel");

		m_sound->SetName("fMeow");

		m_transform->SetPosition(math::Vector3(0, 0, 0));
		m_transform->SetRotation(thomas::math::PI, 0, 0);


		return true;
	}


	void Update()
	{
		//ship controls
		float m_flySpeed = 10;
		if (Input::GetKey(Input::Keys::A))
		{
			m_transform->Translate(-m_transform->Right()*m_flySpeed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::D))
		{
			m_transform->Translate(m_transform->Right()*m_flySpeed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::W))
		{
			m_transform->Translate(m_transform->Forward()*m_flySpeed*Time::GetDeltaTime());
		}
		if (Input::GetKey(Input::Keys::S))
		{
			m_transform->Translate(-m_transform->Forward()*m_flySpeed*Time::GetDeltaTime());
		}

	}

private:
	component::RenderComponent* m_renderer;

	component::SoundComponent* m_sound;

};