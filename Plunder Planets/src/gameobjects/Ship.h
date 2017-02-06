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
		m_cameraObject = Find("CameraObject");

	}

	bool Start()
	{
		m_renderer->SetModel("testModel");

		m_sound->SetName("fMeow");

		m_transform->SetPosition(math::Vector3(0, 0, 0));
		m_transform->SetRotation(thomas::math::PI, 0, 0);

		m_forwardSpeed = 0;
		m_rotationSpeed = 0.1;

		m_accelerationSpeed = 1.5;
		m_retardationSpeed = 0.8;
		m_maxSpeed = 25;

		m_controlSensitivity = 0.1;

		m_cameraSpeed = 3;

		m_cameraObject->m_transform->SetPosition(m_transform->GetPosition() + m_transform->Forward() * 25 + math::Vector3(0, 15, 0));
		return true;
	}


	void Update()
	{
		float dt = Time::GetDeltaTime();
		//ship controls
		if (Input::GetKey(Input::Keys::D))//Constrols inverted, since ship object comes from maya
		{
			//m_transform->Translate(-m_transform->Right()*m_forwardSpeed*dt);
			m_transform->Rotate(m_rotationSpeed * dt, 0, 0);
		}
		if (Input::GetKey(Input::Keys::A))
		{
			
			//m_transform->Translate(m_transform->Right()*m_forwardSpeed*dt);
			m_transform->Rotate(-m_rotationSpeed * dt, 0, 0);
		}
		if (Input::GetKey(Input::Keys::S))
		{
			m_transform->Translate(m_transform->Forward()*m_forwardSpeed*dt);
		}
		if (Input::GetKey(Input::Keys::W))
		{
			m_transform->Translate(-m_transform->Forward()*m_forwardSpeed*dt);
		}
		
		
		if (/*Input::GetLeftStickY() > m_controlSensitivity ||*/ Input::GetButton(Input::Buttons::RT))
		{
			m_forwardSpeed += m_accelerationSpeed * dt;
			m_forwardSpeed = std::fminf(m_forwardSpeed, m_maxSpeed);
			
			m_transform->Translate(-m_transform->Forward() * m_forwardSpeed * dt);
			
			
		}
		else
		{
			m_forwardSpeed -= m_retardationSpeed * dt;
			m_forwardSpeed = std::fmaxf(m_forwardSpeed, 0);

			m_transform->Translate(-m_transform->Forward() * m_forwardSpeed * dt);
		}

		if (m_forwardSpeed > 0)
		{
			float left_x = Input::GetLeftStickX();
			if (std::abs(left_x) > m_controlSensitivity)
			{
				m_transform->Rotate(-left_x * m_rotationSpeed * dt, 0, 0);
			}
			

		}
		float right_x = Input::GetRightStickX();
		float right_y = Input::GetRightStickY();
		float left_y = Input::GetLeftStickY();
		if (std::abs(right_x) > m_controlSensitivity)
		{
			math::Vector3 v = m_transform->GetPosition() - m_cameraObject->m_transform->GetPosition();
			m_cameraObject->m_transform->Translate(v);
			m_cameraObject->m_transform->Rotate(m_cameraSpeed * right_x * dt, 0, 0);
			m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Forward() * v.Length());
			
		}
		if (std::abs(right_y > m_controlSensitivity))
		{
			m_cameraObject->m_transform->Translate(m_transform->Up() * right_y * 20 * dt);
		}
		if (std::abs(left_y) > m_controlSensitivity)
		{
			m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Forward() * left_y * 20 * dt);
		}
		/*else
		{
			m_cameraObject->m_transform->SetPosition(m_transform->GetPosition() + m_transform->Forward() * 25 + math::Vector3(0, 15, 0));
			
		}*/
		m_cameraObject->m_transform->LookAt(m_transform);
	}

private:
	float m_controlSensitivity;

	float m_forwardSpeed;
	float m_rotationSpeed;
	float m_accelerationSpeed;
	float m_retardationSpeed;
	float m_maxSpeed;

	float m_cameraSpeed;


	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	GameObject* m_cameraObject;
};