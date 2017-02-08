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
		m_retardationSpeed = 6.5f;
		m_maxSpeed = 30.0f;

		m_nonBoostMaxSpeed = m_maxSpeed;
		m_nonBoostAcceleration = m_accelerationSpeed;
		m_boostAcceleration = m_accelerationSpeed * 3;
		m_boostMaxSpeed = m_maxSpeed * 2;
		
		m_rotationSpeed = 0.1f;
		m_minmaxRotFactor = 0.45f;
		m_rotation = 0.0f;

		m_controlSensitivity = 0.13f;

		m_elevateCamSpeed = 38;
		m_camZoomSpeed = 45.0f;
		m_camRotationSpeed = 2.0f;
		m_camMinDistanceFromBoat = 20.0f;
		m_camMaxDistanceFromBoat = 120.0f;

		m_cameraObject->m_transform->SetPosition(m_transform->GetPosition() + m_transform->Forward() * 50 + math::Vector3(0, 25, 0));
		m_lookAtOffset = math::Vector3(0, 25, 0);
		m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
		m_cameraObject->m_transform->LookAt(m_lookAtPoint);

		m_vulkanControllsOn = false;


		return true;
	}

	void VulkanControls(float& forwardFactor, float& rightFactor, float const left_x, float const left_y)
	{
		//calculate forward and right contribution of the cam, with the boat, and the controllers left stick
		//these controlls makes for the left stick to match the coordinates of the boat
		//no matter what direction the camera is pointing, the stick will serve in the boats coordinates
		if (left_x != 0 || left_y != 0)
		{
			math::Vector3 camForwardXZ = math::Vector3(m_cameraObject->m_transform->Forward().x, 0, m_cameraObject->m_transform->Forward().z);

			camForwardXZ.Normalize();

			forwardFactor = camForwardXZ.Dot(m_transform->Forward()) * -left_y + camForwardXZ.Dot(m_transform->Right()) * left_x;

			rightFactor = camForwardXZ.Dot(m_transform->Forward()) * left_x + camForwardXZ.Dot(m_transform->Right()) * left_y;

		}
	}

	void Update()
	{
		float dt = Time::GetDeltaTime();
		float right_x = Input::GetRightStickX();
		float right_y = Input::GetRightStickY();
		float left_x = Input::GetLeftStickX();
		float left_y = Input::GetLeftStickY();

		m_modelIndex = (m_modelIndex + 1) % 3;

		m_renderer->SetModel("testModel" + std::to_string(m_modelIndex));

		//for the boost
		if (Input::GetButton(Input::Buttons::LB))
		{
			m_maxSpeed = m_boostMaxSpeed;
			m_accelerationSpeed = m_boostAcceleration;
		}
		else
		{
			m_accelerationSpeed = m_nonBoostAcceleration;
			if (m_nonBoostMaxSpeed < m_forwardSpeed)
			{
				m_forwardSpeed -= m_retardationSpeed * dt;
				m_maxSpeed = m_forwardSpeed;
			}
			else
			{
				m_maxSpeed = m_nonBoostMaxSpeed;
			}
			
		}
		//get forward and right contrib
		float forwardFactor = left_y;
		float rightFactor = -left_x;

		if (m_vulkanControllsOn)
		{
			VulkanControls(forwardFactor, rightFactor, left_x, left_y);
		}
		
		//ship controlls
		if (Input::GetButton(Input::Buttons::RB))
		{
			m_forwardSpeed += m_accelerationSpeed * dt;
			m_forwardSpeed = std::fminf(m_forwardSpeed, m_maxSpeed);
			
		}
		else if (forwardFactor > 0.01f)
		{
			m_forwardSpeed += m_accelerationSpeed * forwardFactor * dt;
			m_forwardSpeed = std::fminf(m_forwardSpeed, m_maxSpeed);
		}
		else
		{
			m_forwardSpeed -= m_retardationSpeed * dt;
			m_forwardSpeed = std::fmaxf(m_forwardSpeed, 0);

		}
		//move the ship
		math::Vector3 moveVec = -m_transform->Forward() * m_forwardSpeed * dt;
		m_transform->Translate(moveVec);
		m_cameraObject->m_transform->Translate(moveVec);//make sure the camera moves with the the ship
		

		if (std::abs(rightFactor) > 0.01)
		{
			m_rotation += m_rotationSpeed * rightFactor * dt;
			m_rotation = std::fmaxf(m_rotation, -m_minmaxRotFactor);
			m_rotation = std::fminf(m_rotation, m_minmaxRotFactor);
		}
		else
		{
			if (m_rotation * m_rotation < 0.004)
			{
				m_rotation = 0;
			}
			else
			{
				if (m_rotation < 0)
				{
					m_rotation += m_rotationSpeed * 1.7f * dt;
				}
				else
				{
					m_rotation -= m_rotationSpeed * 1.7f * dt;
				}
			}
		}
		if (m_forwardSpeed > 0.01)
		{
			m_transform->Rotate(m_rotation * dt, 0, 0);
		}
		
		m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
		math::Vector3 distanceVector = m_lookAtPoint - m_cameraObject->m_transform->GetPosition();

		m_lookAtOffset = math::Vector3(0, distanceVector.Length() / 4, 0);//recalculate lookatoffset depending on camera range from boat
		
		m_cameraObject->m_transform->Translate(distanceVector);//move camera into the boat to make rotations!

		if (std::abs(right_x) > m_controlSensitivity)
		{
			m_cameraObject->m_transform->Rotate(m_camRotationSpeed * right_x * dt, 0, 0);//rotate camera around the boat
		}
		
		m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Forward() * distanceVector.Length());//move the camera back to the distance it was, after rotations
		
		if (std::abs(right_y) > m_controlSensitivity)
		{
			if (m_cameraObject->m_transform->GetPosition().y > 3)
			{
				m_cameraObject->m_transform->Translate(m_transform->Up() * right_y * m_elevateCamSpeed * dt);//move camera up and down
			}
			else if (right_y > m_controlSensitivity)
			{
				m_cameraObject->m_transform->Translate(m_transform->Up() * right_y * m_elevateCamSpeed * dt);//move camera up and down
			}
		}

		m_cameraObject->m_transform->LookAt(m_lookAtPoint);//reset orientation of camera with lookat
		

		//zoom camera in or out. Also make sure that the camera dont get to close to the boat.
		if (distanceVector.Length() > m_camMinDistanceFromBoat)
		{
			if (Input::GetButton(Input::Buttons::DPAD_UP))
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
			if (Input::GetButton(Input::Buttons::DPAD_DOWN))
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
	float m_retardationSpeed;//reverse acceleration is called retardation
	float m_maxSpeed;
	//for the boost
	float m_boostMaxSpeed;
	float m_nonBoostMaxSpeed;
	float m_boostAcceleration;
	float m_nonBoostAcceleration;

	float m_rotationSpeed;
	float m_rotation;//rodret
	float m_minmaxRotFactor;
	//used for the camera
	float m_elevateCamSpeed;//for moving cam up and down
	float m_camRotationSpeed;
	float m_camZoomSpeed;
	float m_camMinDistanceFromBoat;
	float m_camMaxDistanceFromBoat;
	//used for both
	float m_controlSensitivity;
	bool m_vulkanControllsOn;

	math::Vector3 m_lookAtPoint;//point slightly above the boat
	math::Vector3 m_lookAtOffset;

	//components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	GameObject* m_cameraObject;

	int m_modelIndex;

};