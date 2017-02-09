#pragma once
#include <Thomas.h>
#include <string>
#include <algorithm>
#include "Broadside.h"
#include "TerrainObject.h"

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
		m_boostSound = AddComponent<component::SoundComponent>();
		m_cameraObject = Find("CameraObject");
		m_terrainObject = (TerrainObject*)Find("TerrainObject");
		m_treasure = 0;
	}

	bool Start()
	{
		m_broadSideLeft = (Broadside*)Instantiate(new Broadside(), math::Vector3(-3, 3, -0.8), math::Quaternion::CreateFromYawPitchRoll(math::DegreesToradians(-90), 0, 0), m_transform);
		m_broadSideRight = (Broadside*)Instantiate(new Broadside(), math::Vector3(3, 3, -0.8), math::Quaternion::CreateFromYawPitchRoll(math::DegreesToradians(90), 0, 0), m_transform);

		m_treasure = 0;
		m_modelIndex = 0;
		m_renderer->SetModel("testModel0");

		m_boostSound->SetClip("mThomas");
		m_boostSound->SetVolume(0.9);


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
		
		m_rotationSpeed = 0.3f;
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

		m_modelIndex = ((m_modelIndex + 1) % 3) + 1;

		math::Vector3 newForward = math::Vector3(m_transform->Forward().x, 0, m_transform->Forward().z);
		newForward.Normalize();
		m_transform->SetRotation(0, 0, 0);
		m_transform->LookAt(m_transform->GetPosition() + newForward * 3);



		//m_renderer->SetModel("testModel" + std::to_string(m_modelIndex)); //switches between models, activate when boosting

		//for the boost
		if ((Input::GetButton(Input::Buttons::LT) || Input::GetButton(Input::Buttons::A) ) && m_treasure > 50*dt)
		{
			m_treasure -= 50 * dt;
			m_boostRot += dt;
			if (m_boostRot > 1.5)
				m_boostRot = 1.5;
			m_boostSound->Play();
			m_maxSpeed = m_boostMaxSpeed;
			m_accelerationSpeed = m_boostAcceleration;
			m_renderer->SetModel("testModel" + std::to_string(m_modelIndex)); //switches between models, activate when boosting
		}
		else
		{
			m_boostRot = 0;
			m_boostSound->Pause();
			m_accelerationSpeed = m_nonBoostAcceleration;
			m_renderer->SetModel("testModel0"); //reset to default Mesh
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
		if (Input::GetButton(Input::Buttons::RT))
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

		if (m_terrainObject->Collision(math::Vector2(m_transform->GetPosition().x, m_transform->GetPosition().z)))
		{
			m_forwardSpeed = min(m_forwardSpeed, m_maxSpeed/2);
		}

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
					m_rotation += m_rotationSpeed * dt;
				}
				else
				{
					m_rotation -= m_rotationSpeed * dt;
				}
			}
		}
		if (m_forwardSpeed > 0.01)
		{
			

			m_transform->Rotate(m_rotation * dt, 0, 0);
			
		}

		//if (m_boostRot == 0 && m_transform->GetPosition().y > -0.8)
		//{
		//	m_fallSpeed += -9.82 * dt;
		//	m_transform->Translate(math::Vector3(0, m_fallSpeed *dt, 0));
		//}
		//else if (m_boostRot == 0)
		//{
		//	m_fallSpeed = 0;
		//	math::Vector3 newForward = math::Vector3(m_transform->Forward().x, 0, m_transform->Forward().z);
		//	newForward.Normalize();
		//	m_transform->SetRotation(0, 0, 0);
		//	m_transform->LookAt(m_transform->GetPosition() + newForward * 3);
		//	
		//	float rollAngle = m_transform->Up().Dot(math::Vector3(0, 1, 0));
		//	
		//}
		
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


		if(Input::GetButtonDown(Input::Buttons::RB))
			m_broadSideRight->Fire(-m_forwardSpeed);

		if (Input::GetButtonDown(Input::Buttons::LB))
			m_broadSideLeft->Fire(m_forwardSpeed);


		m_soundDelayLeft -= dt;
		if (m_forwardSpeed != 0.0 && m_soundDelayLeft < 0)
		{
			m_sound->PlayOneShot(m_SFXs[rand() % 9], 1);
			m_soundDelayLeft = m_soundDelay;
		}

		PlunderIsland();



		newForward = math::Vector3(m_transform->Forward().x, m_boostRot*math::DegreesToradians(-10), m_transform->Forward().z);
		newForward.Normalize();
		m_transform->SetRotation(0, 0, 0);
		m_transform->LookAt(m_transform->GetPosition() + newForward * 3);

	}

	void PlunderIsland()
	{
		math::Vector2 shipPos = math::Vector2(m_transform->GetPosition().x, m_transform->GetPosition().z);
		m_treasure += m_terrainObject->Plunder(shipPos);
	}

	int GetTreasure()
	{
		return m_treasure + 0.5;
	}
private:
	
	//used for the boat
	float m_forwardSpeed;
	
	float m_accelerationSpeed;
	float m_retardationSpeed;//reverse acceleration is called retardation
	float m_maxSpeed;

	float m_treasure;

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
	component::SoundComponent* m_boostSound;
	GameObject* m_cameraObject;
	TerrainObject* m_terrainObject;

	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRight;

	int m_modelIndex;

	float m_soundDelay = 5;
	float m_soundDelayLeft = 5;


	float m_boostRot = 0;
	float m_fallSpeed = 0;

	std::string m_SFXs[9] = {
		"fCreak1",
		"fCreak2",
		"fCreak3",
		"fCreak4",
		"fDoubleCreak1",
		"fDoubleCreak2",
		"fDoubleCreak3",
		"fSlowCreak1",
		"fSlowCreak2"
	};

};