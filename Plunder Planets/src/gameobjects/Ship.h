#pragma once
#include <Thomas.h>
#include <string>
#include <algorithm>
#include "Broadside.h"
#include "TerrainObject.h"
#include "WaterObject.h"
#include "ShipFloat.h"
#include "PhysicsObject.h"
using namespace thomas;
using namespace object;
class Ship : public GameObject
{

private:

public:
	Ship() : GameObject("Ship")
	{
	}

	void Start()
	{

		m_freeCamera = false;
		utils::DebugTools::AddBool(m_freeCamera, "Free Camera");

		float mass = 5000;
		//Front
		m_floats[0] = Instantiate<ShipFloat>(math::Vector3(1.5, 0, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[1] = Instantiate<ShipFloat>(math::Vector3(-1.5, 0, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[0]->SetMass(0.10*mass);
		m_floats[1]->SetMass(0.10*mass);
		//front middle
		m_floats[2] = Instantiate<ShipFloat>(math::Vector3(3, 0, 5), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[3] = Instantiate<ShipFloat>(math::Vector3(-3, 0, 5), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[2]->SetMass(0.12*mass);
		m_floats[3]->SetMass(0.12*mass);
		//back middle
		m_floats[4] = Instantiate<ShipFloat>(math::Vector3(3, 0, -1), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[5] = Instantiate<ShipFloat>(math::Vector3(-3, 0, -1), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[4]->SetMass(0.13*mass);
		m_floats[5]->SetMass(0.13*mass);
		//back
		m_floats[6] = Instantiate<ShipFloat>(math::Vector3(2.5, 0, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[7] = Instantiate<ShipFloat>(math::Vector3(-2.5, 0, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[6]->SetMass(0.15*mass);
		m_floats[7]->SetMass(0.15*mass);
		m_transform->SetPosition(0, 0.5, 0);

		m_renderer = AddComponent<component::RenderComponent>();
		m_sound = AddComponent<component::SoundComponent>();
		m_boostSound = AddComponent<component::SoundComponent>();
		m_cameraObject = Find("CameraObject");
		m_terrainObject = (TerrainObject*)Find("TerrainObject");
		m_rigidBody = AddComponent<component::RigidBodyComponent>();
		//Detta funkar fan inte
		m_broadSideLeft = Instantiate<Broadside>(math::Vector3(-5.5, 6, -2.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0,1,0), math::DegreesToradians(90)), m_transform, m_scene);
		m_broadSideRight = Instantiate<Broadside>(math::Vector3(5.5, 6, -2.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToradians(270)), m_transform, m_scene);
		m_broadSideLeft->CreateCanons();
		m_broadSideRight->CreateCanons();

		//Rigidbody init
		m_rigidBody->SetMass(5000);
		m_rigidBody->SetCollider(new btBoxShape(btVector3(3, 12, 8)));
		m_rigidBody->setSleepingThresholds(0.2, 0.5);

		m_treasure = 10000;

		//model
		m_modelIndex = 0;
		m_renderer->SetModel("testModel0");

		//sound
		m_boostSound->SetClip("mThomas");
		m_boostSound->SetVolume(0.9);
		m_soundDelay = 5;
		m_soundDelayLeft = 5;
		//movement
		m_forwardSpeed = 0;
		m_accelerationSpeed = 9.5f;
		m_retardationSpeed = 6.5f;
		m_maxSpeed = 30.0f;

		m_boostRot = 0;
		m_nonBoostMaxSpeed = m_maxSpeed;
		m_nonBoostAcceleration = m_accelerationSpeed;
		m_boostAcceleration = m_accelerationSpeed * 3;
		m_boostMaxSpeed = m_maxSpeed * 2;
		
		m_rotationSpeed = 0.3f;
		m_minmaxRotFactor = 0.45f;
		m_rotation = 0.0f;

		//gravity
		m_fallSpeed = 0;
		m_inAir = false;
		m_mass = 10;
		//controlls/camera
		m_controlSensitivity = 0.13f;

		m_elevateCamSpeed = 38;
		m_camZoomSpeed = 45.0f;
		m_camRotationSpeed = 2.0f;
		m_camMinDistanceFromBoat = 20.0f;
		m_camMaxDistanceFromBoat = 220.0f;

		m_cameraObject->m_transform->SetPosition(m_transform->GetPosition() + m_transform->Forward() * 200 + math::Vector3(0, 25, 0));
		m_lookAtOffset = math::Vector3(0, 20, 0);
		m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
		m_cameraObject->m_transform->LookAt(m_lookAtPoint);


		m_retardControllsOn = false;
		m_gravity = 0;
		damp = 0.9;
	}

	void RetardControls(float& forwardFactor, float& rightFactor, float& upFactorPitch, float&upFactorRoll, float const left_x, float const left_y)//does not work with flying right now
	{
		//The left stick controlls the ship ASWELL as its orientation. The position of the camera changes the way the boat is maneuvered
		if (left_x != 0 || left_y != 0)
		{
			math::Vector3 camForwardXZ = math::Vector3(m_cameraObject->m_transform->Forward().x, 0, m_cameraObject->m_transform->Forward().z);
			camForwardXZ.Normalize();

			float d1 = camForwardXZ.Dot(m_transform->Forward());
			float d2 = camForwardXZ.Dot(m_transform->Right());

			forwardFactor = d1 * -left_y + d2 * left_x;

			rightFactor = d1 * left_x + d2 * left_y;

			upFactorPitch = m_transform->Forward().Dot(math::Vector3(0, 0, -1)) * left_y * -d1 + m_transform->Forward().Dot(math::Vector3(0, 0, -1)) * left_x * d2;
			upFactorRoll = m_transform->Forward().Dot(math::Vector3(1, 0, 0)) * left_y * -d1 + m_transform->Forward().Dot(math::Vector3(1, 0, 0)) * left_x * d2;

		
		}
	}

	void ShipBoost(float const dt)
	{
		//for the boost
		if ((Input::GetButton(Input::Buttons::LT) || Input::GetButton(Input::Buttons::A) ) && m_treasure > 50*dt)
		{
			m_treasure -= 50 * dt;
			
			m_boostRot = 1;
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
	}
		
	void ShipMove(float const forwardFactor, float const dt)
	{
		//ship controlls
		if (Input::GetButton(Input::Buttons::RT) || Input::GetButton(Input::Buttons::LT) || Input::GetButton(Input::Buttons::A))
		{
			m_forwardSpeed += m_accelerationSpeed * dt;
			m_forwardSpeed = std::fminf(m_forwardSpeed, m_maxSpeed);
			
		}
		else if (forwardFactor > 0.01f)//for retardcontrols
		{
			m_forwardSpeed += m_accelerationSpeed * forwardFactor * dt;
			m_forwardSpeed = std::fminf(m_forwardSpeed, m_maxSpeed);
		}
		else
		{
			m_forwardSpeed -= m_retardationSpeed * dt;
			m_forwardSpeed = std::fmaxf(m_forwardSpeed, 0);

		}
		

		math::Vector3 moveVec = -m_transform->Forward() * m_forwardSpeed * dt;
		m_transform->Translate(moveVec);
		m_cameraObject->m_transform->Translate(moveVec);//make sure the camera moves with the the ship
	}
		
	void ShipRotate(float const  rightFactor, float const dt)
	{
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
		m_transform->Rotate(m_rotation * dt, 0, 0);
	}

	void ShipFly(float const upFactorPitch, float const upFactorRoll, float const left_y, float const dt)
	{
		if (!m_inAir && left_y < 0)
		{
			m_transform->Rotate(0, m_boostRot * dt * upFactorPitch * m_rotationSpeed, m_boostRot * dt * upFactorRoll * m_rotationSpeed);
			m_inAir = true;
		}
		else if (m_inAir)
		{
			m_transform->Rotate(0, dt * upFactorPitch * m_rotationSpeed, dt * upFactorRoll * m_rotationSpeed);
		}

	}
		
	void ShipFireCannons()
	{
		if (Input::GetKeyDown(Input::Keys::Space))
		{
			m_broadSideRight->Fire(-m_forwardSpeed);
			m_broadSideLeft->Fire(m_forwardSpeed);
		}
	}
	//cam
	void CameraRotate(float const right_x, float const right_y, float const dt, math::Vector3 const distanceVector)
	{
		m_cameraObject->m_transform->Translate(distanceVector);//move camera into the boat to make rotations for the camera!
		if (std::abs(right_x) > m_controlSensitivity || std::abs(right_y) > m_controlSensitivity)
		{
			float angle = std::acos(m_cameraObject->m_transform->Forward().Dot(math::Vector3(0, 1, 0))) * 180 / math::PI;
			m_cameraObject->m_transform->Rotate(m_camRotationSpeed * right_x * dt, 0, 0);
			bool allowRotation = true;

			if (angle > 160)
			{
				if (right_y > 0)
				{
					allowRotation = false;
				}
			}
			else if (angle < 20)
			{
				if (right_y < 0)
				{
					allowRotation = false;
				}
			}
			
			if (allowRotation)//anti gimballock
			{
				m_cameraObject->m_transform->Rotate(0, m_cameraObject->m_transform->Forward().Dot(math::Vector3(0, 0, 1)) * m_camRotationSpeed * right_y * dt, m_cameraObject->m_transform->Forward().Dot(math::Vector3(-1, 0, 0)) * m_camRotationSpeed * right_y * dt);//rotate camera around the boat
			}
			
			
		}
		
		m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Forward() * distanceVector.Length());//move the camera back to the distance it was, after rotations
	}

	void CameraZoom(math::Vector3 const distanceVector, float const dt)
	{
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

	void PlaySounds(float const dt)
	{
		m_soundDelayLeft -= dt;
		if (m_forwardSpeed != 0.0 && m_soundDelayLeft < 0)
		{
			m_sound->PlayOneShot(m_SFXs[rand() % 9], 1);
			m_soundDelayLeft = m_soundDelay;
		}
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

	void Update()
	{
	

		float const dt = Time::GetDeltaTime();
		float const right_x = Input::GetRightStickX();
		float const right_y = Input::GetRightStickY();
		float const left_x = Input::GetLeftStickX();
		float const left_y = Input::GetLeftStickY();

		//get forward, right and up contrib
		float forwardFactor = 0;
		float rightFactor = -left_x;
		float upFactorPitch = m_transform->Forward().Dot(math::Vector3(0, 0, -1)) * left_y;
		float upFactorRoll = m_transform->Forward().Dot(math::Vector3(1, 0, 0)) * left_y;

		m_modelIndex = ((m_modelIndex + 1) % 3) + 1;

		//ShipBoost(dt);
		
		
		//Ship Movement
		ShipMove(forwardFactor, dt);
		ShipRotate(rightFactor, dt);
		ShipFly(upFactorPitch, upFactorRoll, left_y, dt);
		ShipFireCannons();
		

		if (!m_freeCamera)
		{
			//Recalculate look at point and the new distance from cam to ship
			m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
			math::Vector3 const distanceVector = m_lookAtPoint - m_cameraObject->m_transform->GetPosition();

			m_lookAtOffset = math::Vector3(0, (distanceVector.Length() / 4) + 5, 0);//recalculate lookatoffset depending on camera range from boat

			CameraRotate(right_x, right_y, dt, distanceVector);
			m_cameraObject->m_transform->SetRotation(0, 0, 0); //reset rotation
			m_cameraObject->m_transform->LookAt(m_lookAtPoint);//reset to planar orientation of camera with lookat
			CameraZoom(distanceVector, dt);
		}

		
		PlaySounds(dt);
		
		PlunderIsland();

		

		bool inWater = false;

		for (int i = 0; i < 4; i++)
		{
			bool wTemp = m_floats[i]->UpdateBoat(m_rigidBody);
			if (wTemp)
				inWater = true;
		}

		for (int i = 0; i < 8; i++)
		{
			bool wTemp = m_floats[i]->UpdateBoat(m_rigidBody);
			if (wTemp)
				inWater = true;
		}

		if (inWater)
		{
			LOG("in water");
		}
		else
		{
			LOG("not in water");
			m_rigidBody->setDamping(0.0, 0.0);
		}

		if (Input::GetKey(Input::Keys::Up))
			m_rigidBody->applyCentralForce(*(btVector3*)&(-m_transform->Forward() * 1000000));

		
	}

private:
	

	float damp;

	bool m_freeCamera;

	//used for the boat
	float m_forwardSpeed;
	
	float m_accelerationSpeed;
	float m_retardationSpeed;//reverse acceleration is called retardation
	float m_maxSpeed;

	float m_treasure;
	float m_mass;

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
	bool m_retardControllsOn;

	math::Vector3 m_lookAtPoint;//point slightly above the boat
	math::Vector3 m_lookAtOffset;
	math::Vector3 m_initPosition;

	//components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	component::SoundComponent* m_boostSound;
	component::RigidBodyComponent* m_rigidBody;
	ShipFloat* m_floats[8];
	GameObject* m_cameraObject;
	TerrainObject* m_terrainObject;

	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRight;

	int m_modelIndex;

	float m_soundDelay;
	float m_soundDelayLeft;


	float m_boostRot;
	float m_fallSpeed;
	float m_gravity;
	bool m_inAir;

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