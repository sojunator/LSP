#pragma once
#include <Thomas.h>
#include <string>
#include <algorithm>


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

		m_modelIndex = 0;
		m_renderer->SetModel("testModel0");

		m_sound->SetName("fMeow");

		m_transform->SetPosition(math::Vector3(0, -0.8, 0));
		m_transform->SetRotation(thomas::math::PI, 0, 0);

		m_forwardSpeed = 0;
		
		m_accelerationSpeed = 9.5f;
		m_retardationSpeed = 0.8f;
		m_maxSpeed = 30.0f;
		
		m_rotationSpeed = 0.0f;
		m_rotationAccelerationSpeed = 0.5f;
		m_rotationMaxSpeed = 4.9f;

		m_controlSensitivity = 0.13f;

		m_camZoomSpeed = 25;
		m_camRotationSpeed = 5.0f;
		m_camMinDistanceFromBoat = 10;
		m_camMaxDistanceFromBoat = 55;

		m_cameraObject->m_transform->SetPosition(m_transform->GetPosition() + m_transform->Forward() * 25 + math::Vector3(0, 15, 0));
		m_cameraObject->m_transform->LookAt(m_transform);
		return true;
	}


	void Update()
	{
		float dt = Time::GetDeltaTime();
		
		m_modelIndex = (m_modelIndex + 1) % 3;
		

		//m_renderer->SetModel("testModel" + std::to_string(m_modelIndex)); //switches between models, activate when boosting


		//ship controlls
		if (Input::GetButton(Input::Buttons::RT))
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

		float left_x = Input::GetLeftStickX();
		if (m_forwardSpeed > 1.0f)
		{
			if (std::abs(left_x) > m_controlSensitivity)
			{
				m_rotationSpeed += m_rotationAccelerationSpeed *dt;
				m_rotationSpeed = std::fminf(m_rotationSpeed, m_rotationMaxSpeed);
				m_transform->Rotate(-left_x * m_rotationSpeed * dt, 0, 0);
			}
			else
			{
				m_rotationSpeed -= m_rotationAccelerationSpeed *dt;
				m_rotationSpeed = std::fmaxf(m_rotationSpeed, 0);
				m_transform->Rotate(-left_x * m_rotationSpeed * dt, 0, 0);
			}
		}
		
		float right_x = Input::GetRightStickX();
		float right_y = Input::GetRightStickY();

		math::Vector3 distanceVector = m_transform->GetPosition() - m_cameraObject->m_transform->GetPosition();
		
		m_cameraObject->m_transform->Translate(distanceVector);//move camera into the boat to make rotations!

		if (std::abs(right_x) > m_controlSensitivity)
		{
			m_cameraObject->m_transform->Rotate(m_camRotationSpeed * right_x * dt, 0, 0);//rotate camera around the boat
		}
		
		m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Forward() * distanceVector.Length());//move the camera back to the distance it was, after rotations
		
		if (std::abs(right_y) > m_controlSensitivity)
		{
			m_cameraObject->m_transform->Translate(m_transform->Up() * right_y * 20 * dt);//move camera up and down
		}

		m_cameraObject->m_transform->LookAt(m_transform);//reset orientation of camera with lookat
		

		//zoom camera in or out. Also make sure that the camera dont get to close to the boat.
		if (distanceVector.Length() > m_camMinDistanceFromBoat)
		{
			if (Input::GetButton(Input::Buttons::RB))
			{
				m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Forward() * m_camZoomSpeed * dt);
			}
		}
		else
		{
			m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Forward() * (m_camMinDistanceFromBoat - distanceVector.Length()));
		}
		if (distanceVector.Length() < m_camMaxDistanceFromBoat)
		{
			if (Input::GetButton(Input::Buttons::LB))
			{
				m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Forward() * m_camZoomSpeed * dt);
			}
		}
		else
		{
			m_cameraObject->m_transform->Translate(m_cameraObject->m_transform->Forward() * (distanceVector.Length() - m_camMaxDistanceFromBoat));
		}
	}

private:
	
	//used for the boat
	float m_forwardSpeed;
	
	float m_accelerationSpeed;
	float m_retardationSpeed;
	float m_maxSpeed;

	float m_rotationSpeed;
	float m_rotationAccelerationSpeed;
	float m_rotationMaxSpeed;
	//used for the camera
	float m_camZoomSpeed;
	float m_camRotationSpeed;
	float m_camMinDistanceFromBoat;
	float m_camMaxDistanceFromBoat;
	//used for both
	float m_controlSensitivity;

	//components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	GameObject* m_cameraObject;

	int m_modelIndex;

};