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

		float mass = 20000;
		//Front
		m_floats[0] = Instantiate<ShipFloat>(math::Vector3(1.5, 0, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[1] = Instantiate<ShipFloat>(math::Vector3(-1.5, 0, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[0]->SetMass(0.13*mass);
		m_floats[1]->SetMass(0.13*mass);
		//front middle
		m_floats[2] = Instantiate<ShipFloat>(math::Vector3(3, 0, 5), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[3] = Instantiate<ShipFloat>(math::Vector3(-3, 0, 5), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[2]->SetMass(0.11*mass);
		m_floats[3]->SetMass(0.11*mass);
		//back middle
		m_floats[4] = Instantiate<ShipFloat>(math::Vector3(3, 0, -1), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[5] = Instantiate<ShipFloat>(math::Vector3(-3, 0, -1), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[4]->SetMass(0.12*mass);
		m_floats[5]->SetMass(0.12*mass);
		//back
		m_floats[6] = Instantiate<ShipFloat>(math::Vector3(2.5, 0, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[7] = Instantiate<ShipFloat>(math::Vector3(-2.5, 0, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[6]->SetMass(0.14*mass);
		m_floats[7]->SetMass(0.14*mass);

		//stabilizers front
		m_floats[8] = Instantiate<ShipFloat>(math::Vector3(2.5, 5, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[9] = Instantiate<ShipFloat>(math::Vector3(-2.5, 5, 8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[8]->SetMass(0.5*mass);
		m_floats[9]->SetMass(0.5*mass);
		//stabilizers back
		m_floats[10] = Instantiate<ShipFloat>(math::Vector3(2.5, 5, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[11] = Instantiate<ShipFloat>(math::Vector3(-2.5, 5, -8), math::Quaternion::Identity, m_transform, m_scene);
		m_floats[10]->SetMass(0.5*mass);
		m_floats[11]->SetMass(0.5*mass);

		m_transform->SetPosition(0, 0.5, 0);

		m_renderer = AddComponent<component::RenderComponent>();
		m_sound = AddComponent<component::SoundComponent>();
		m_boostSound = AddComponent<component::SoundComponent>();
		m_cameraObject = Find("CameraObject");
		m_terrainObject = (TerrainObject*)Find("TerrainObject");
		m_rigidBody = AddComponent<component::RigidBodyComponent>();

		m_broadSideLeft = Instantiate<Broadside>(math::Vector3(-5.5, 6, -2.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToradians(90)), m_transform, m_scene);
		m_broadSideRight = Instantiate<Broadside>(math::Vector3(5.5, 6, -2.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToradians(270)), m_transform, m_scene);
		m_broadSideLeft->CreateCanons();
		m_broadSideRight->CreateCanons();

		//Rigidbody init
		m_rigidBody->SetMass(20000);
		m_rigidBody->SetCollider(new btBoxShape(btVector3(3, 20, 8)));
		m_rigidBody->setSleepingThresholds(0.2, 0.5);

		m_treasure = 10000;

		//model
		m_modelIndex = 1;
		m_renderer->SetModel("testModel0");
		m_moving = false;
		//sound

		m_boostSound->SetClip("fFlames");
		m_boostSound->SetVolume(1000);
		m_soundDelay = 5;
		m_soundDelayLeft = 5;
		//movement
		m_speed = 2000;
		utils::DebugTools::AddFloat(m_speed, "boatSpeed");
		m_turnSpeed = 2000;
		utils::DebugTools::AddFloat(m_turnSpeed, "boatTurnSpeed");

		m_flyTurnSpeed = 500;
		utils::DebugTools::AddFloat(m_flyTurnSpeed, "boatFlyTurnSpeed");
		//controlls/camera
		m_controlSensitivity = 0.13f;

		m_elevateCamSpeed = 38;
		m_camZoomSpeed = 45.0f;
		m_camRotationSpeed = 2.0f;
		m_camMinDistanceFromBoat = 20.0f;
		m_camMaxDistanceFromBoat = 220.0f;
		m_cameraDistance = 50.0;

		m_cameraObject->m_transform->SetPosition(m_transform->GetPosition() + m_transform->Forward() * 200 + math::Vector3(0, 25, 0));
		m_lookAtOffset = math::Vector3(0, 20, 0);
		m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
		m_cameraObject->m_transform->LookAt(m_lookAtPoint);

	}


	void ShipMove(float const dt)
	{
		//ship controlls
		if (Input::GetButton(Input::Buttons::RT) || Input::GetKey(Input::Keys::W))
		{
			math::Vector3 forward = m_transform->Forward();
			//Remove y part;
			forward.y = 0;
			m_moving = true;
			m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed*dt*m_rigidBody->GetMass()));
		}
	}

	void ShipRotate(float const dt)
	{
		float turnDelta = -Input::GetLeftStickX();
		math::Vector3 right = m_transform->Right();
		//Remove y part;
		right.y = 0;
		m_rigidBody->activate();
		m_rigidBody->applyTorque(btVector3(0, m_turnSpeed*turnDelta*dt*m_rigidBody->GetMass(), 0));
	}

	void ShipFly(float const upFactorPitch, float const upFactorRoll, float const left_y, float const dt)
	{
		if (Input::GetButton(Input::Buttons::LT) || Input::GetButton(Input::Buttons::A) || Input::GetKey(Input::Keys::Space))
		{
			math::Vector3 forward = m_transform->Forward();
			m_moving = true;
			forward.y = 0;
			m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * 2 * m_speed*dt*m_rigidBody->GetMass()));
			float turnDelta = -Input::GetLeftStickY();

			/*m_rigidBody->applyForce(btVector3(0, turnDelta*m_flyTurnSpeed*dt*m_rigidBody->GetMass(), 0), btVector3(0,0,8));
			btVector3 angular = m_rigidBody->getAngularVelocity();
			m_rigidBody->setAngularVelocity(btVector3(angular.x(), angular.y(), 0));*/
			m_flying = true;
		}
	}

	void ShipFireCannons()
	{
		if (Input::GetButtonDown(Input::Buttons::RB) || Input::GetKey(Input::Keys::E))
			m_broadSideRight->Fire();

		if (Input::GetButtonDown(Input::Buttons::LB) || Input::GetKey(Input::Keys::Q))
			m_broadSideLeft->Fire();

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

	void CameraZoom(float const dt)
	{

		if (Input::GetButton(Input::Buttons::DPAD_UP))
		{
			m_cameraDistance -= m_camZoomSpeed*dt;
		}
		
		if (Input::GetButton(Input::Buttons::DPAD_DOWN))
		{
			m_cameraDistance += m_camZoomSpeed*dt;
		}

		if (m_cameraDistance > m_camMaxDistanceFromBoat)
			m_cameraDistance = m_camMaxDistanceFromBoat;

		if (m_cameraDistance < m_camMinDistanceFromBoat)
			m_cameraDistance = m_camMinDistanceFromBoat;
	
	}

	void PlaySounds(float const dt)
	{
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
		float right_x = Input::GetRightStickX();
		float right_y = Input::GetRightStickY();
		float left_x = Input::GetLeftStickX();
		float left_y = Input::GetLeftStickY();

		//If cam changed with arrow keys
		if (Input::GetKey(Input::Keys::Right))
			right_x = -Input::GetKey(Input::Keys::Right);
		else if (Input::GetKey(Input::Keys::Left))
			right_x = Input::GetKey(Input::Keys::Left);

		if (Input::GetKey(Input::Keys::Up))
			right_y = Input::GetKey(Input::Keys::Up);
		else if (Input::GetKey(Input::Keys::Down))
			right_y = -Input::GetKey(Input::Keys::Down);

		//If boat turning with A / D
		if (Input::GetKey(Input::Keys::D))
			left_x = Input::GetKey(Input::Keys::D);
		else if (Input::GetKey(Input::Keys::A))
			left_x = -Input::GetKey(Input::Keys::A);

		//get forward, right and up contrib
		float forwardFactor = 0;
		float rightFactor = -left_x;
		float upFactorPitch = m_transform->Forward().Dot(math::Vector3(0, 0, -1)) * left_y;
		float upFactorRoll = m_transform->Forward().Dot(math::Vector3(1, 0, 0)) * left_y;

		m_modelIndex = ((m_modelIndex + 1) % 3) + 1;

		//ShipBoost(dt);

		if (!m_freeCamera)
		{
			CameraZoom(dt);

			//Recalculate look at point and the new distance from cam to ship
			m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
			math::Vector3 const distanceVector = m_lookAtPoint - m_cameraObject->m_transform->GetPosition();

			m_lookAtOffset = math::Vector3(0, (distanceVector.Length() / 4) + 5, 0);//recalculate lookatoffset depending on camera range from boat

			CameraRotate(right_x, right_y, dt, distanceVector);




			//Move camera "distance" away from boat.
			//math::Vector3 newPos = m_lookAtPoint - (m_cameraObject->m_transform->Forward()*distance);
			//
			//newPos = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), newPos, dt*2.5);

			//m_cameraObject->m_transform->SetPosition(newPos);

			//move camera behind boat
			math::Vector3 posBehindBoat = m_lookAtPoint + (m_transform->Forward()*m_cameraDistance);
			posBehindBoat.y = 25;

			posBehindBoat = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), posBehindBoat, dt);

			m_cameraObject->m_transform->SetPosition(posBehindBoat);

			m_cameraObject->m_transform->SetRotation(0, 0, 0); //reset rotation
			m_cameraObject->m_transform->LookAt(m_lookAtPoint);//reset to planar orientation of camera with lookat

			math::Vector3 newPos = m_lookAtPoint - (m_cameraObject->m_transform->Forward()*m_cameraDistance);

			newPos = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), newPos, dt*2.5);

			m_cameraObject->m_transform->SetPosition(newPos);

		}
		m_moving = false;
		m_flying = false;
		//Ship Movement
		ShipMove(dt);
		ShipRotate(dt);
		ShipFly(upFactorPitch, upFactorRoll, left_y, dt);
		ShipFireCannons();

		if (m_flying)
		{
			m_renderer->SetModel("testModel" + std::to_string(m_modelIndex));
			m_boostSound->Play();
		}
		else
		{
			m_renderer->SetModel("testModel0");
			m_boostSound->Pause();
		}



		PlaySounds(dt);

		PlunderIsland();



		bool inWater = false;


		for (int i = 0; i < 12; i++)
		{
			bool wTemp = m_floats[i]->UpdateBoat(m_rigidBody, m_moving);
			if (wTemp)
				inWater = true;
		}

		if (!inWater)
		{
			m_rigidBody->setDamping(0.0, 0.0);
		}


	}

private:

	bool m_moving;
	float damp;

	bool m_freeCamera;
	bool m_flying;
	float m_treasure;
	float m_mass;
	float m_flyTurnSpeed;
	float m_speed;
	float m_turnSpeed;
	//used for the camera
	float m_elevateCamSpeed;//for moving cam up and down
	float m_camRotationSpeed;
	float m_camZoomSpeed;
	float m_cameraDistance;
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
	ShipFloat* m_floats[12];
	GameObject* m_cameraObject;
	TerrainObject* m_terrainObject;

	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRight;

	int m_modelIndex;

	float m_soundDelay;
	float m_soundDelayLeft;


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