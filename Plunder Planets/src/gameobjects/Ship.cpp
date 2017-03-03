#include "ship.h"
#include "TerrainObject.h"
#include "Wormhole.h"
void Ship::Start()
{
	m_freeCamera = false;
	utils::DebugTools::AddBool(m_freeCamera, "Free camera");

	float mass = 20000;
	//Front
	m_floats[0] = Instantiate<ShipFloat>(math::Vector3(1.5, -0.5, 8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[1] = Instantiate<ShipFloat>(math::Vector3(-1.5, -0.5, 8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[0]->SetMass(0.13*mass);
	m_floats[1]->SetMass(0.13*mass);
	//front middle
	m_floats[2] = Instantiate<ShipFloat>(math::Vector3(3, -0.5, 5), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[3] = Instantiate<ShipFloat>(math::Vector3(-3, -0.5, 5), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[2]->SetMass(0.11*mass);
	m_floats[3]->SetMass(0.11*mass);
	//back middle
	m_floats[4] = Instantiate<ShipFloat>(math::Vector3(3, -0.5, -1), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[5] = Instantiate<ShipFloat>(math::Vector3(-3, -0.5, -1), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[4]->SetMass(0.12*mass);
	m_floats[5]->SetMass(0.12*mass);
	//back
	m_floats[6] = Instantiate<ShipFloat>(math::Vector3(2.5, -0.5, -8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[7] = Instantiate<ShipFloat>(math::Vector3(-2.5, -0.5, -8), math::Quaternion::Identity, m_transform, m_scene);
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

	m_renderer = AddComponent<component::RenderComponent>();
	m_sound = AddComponent<component::SoundComponent>();
	m_boostSound = AddComponent<component::SoundComponent>();
	m_cameraObject = Find("CameraObject");
	m_terrainObject = (TerrainObject*)Find("TerrainObject");
	m_waterObject = (WaterObject*)Find("WaterObject");
	m_rigidBody = AddComponent<component::RigidBodyComponent>();

	m_broadSideLeft = Instantiate<Broadside>(math::Vector3(-6, 10, 2.3), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToRadians(90)), m_transform, m_scene);
	m_broadSideRight = Instantiate<Broadside>(math::Vector3(6, 10, -2.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToRadians(270)), m_transform, m_scene);
	m_broadSideLeft->CreateCannons();
	m_broadSideRight->CreateCannons();

	
	m_boosterParticlesEmitterLeft1 = AddComponent<component::ParticleEmitterComponent>();
	m_boosterParticlesEmitterLeft1->SetTexture("../res/textures/fire.png");
	m_boosterParticlesEmitterLeft1->SetShader("particleShader");
	m_boosterParticlesEmitterLeft1->SetEmissionRate(2500);
	m_boosterParticlesEmitterLeft1->SetEmissionDuration(0.1f);
	m_boosterParticlesEmitterLeft1->SetStartColor(math::Vector4(1.0f, 0.3f, 0.0f, 1.0f));
	m_boosterParticlesEmitterLeft1->SetEndColor(math::Vector4(1.0f, 1.0f, 0.0f, 0.5f));
	m_boosterParticlesEmitterLeft1->SetMaxSpeed(20.0f);
	m_boosterParticlesEmitterLeft1->SetMinSpeed(13.0f);
	m_boosterParticlesEmitterLeft1->SetMaxSize(0.8f);
	m_boosterParticlesEmitterLeft1->SetMinSize(0.4f);
	m_boosterParticlesEmitterLeft1->SetEndSize(0.0f);
	m_boosterParticlesEmitterLeft1->SetMaxLifeTime(0.25f);
	m_boosterParticlesEmitterLeft1->SetMinLifeTime(0.15f);
	m_boosterParticlesEmitterLeft1->SetRotationSpeed(10.0f);
	m_boosterParticlesEmitterLeft1->SetRadius(2.2f);
	m_boosterParticlesEmitterLeft1->SpawnAtSphereEdge(true);
	m_boosterParticlesEmitterLeft1->SetSpread(2.7f);

	m_boosterParticlesEmitterLeft2 = AddComponent<component::ParticleEmitterComponent>();
	m_boosterParticlesEmitterLeft2->SetTexture("../res/textures/fire2.png");
	m_boosterParticlesEmitterLeft2->SetShader("particleShader");
	m_boosterParticlesEmitterLeft2->SetEmissionRate(5000);
	m_boosterParticlesEmitterLeft2->SetEmissionDuration(0.1f);
	m_boosterParticlesEmitterLeft2->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_boosterParticlesEmitterLeft2->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
	m_boosterParticlesEmitterLeft2->SetMaxSpeed(10.0f);
	m_boosterParticlesEmitterLeft2->SetMinSpeed(6.0f);
	m_boosterParticlesEmitterLeft2->SetMaxSize(0.6f);
	m_boosterParticlesEmitterLeft2->SetMinSize(0.3f);
	m_boosterParticlesEmitterLeft2->SetEndSize(0.0f);
	m_boosterParticlesEmitterLeft2->SetMaxLifeTime(0.8f);
	m_boosterParticlesEmitterLeft2->SetMinLifeTime(0.3f);
	m_boosterParticlesEmitterLeft2->SetRotationSpeed(2.0f);
	m_boosterParticlesEmitterLeft2->SetSpread(2.5f);

	m_boosterParticlesEmitterRight1 = AddComponent<component::ParticleEmitterComponent>();
	m_boosterParticlesEmitterRight1->SetTexture("../res/textures/fire.png");
	m_boosterParticlesEmitterRight1->SetShader("particleShader");
	m_boosterParticlesEmitterRight1->SetEmissionRate(2500);
	m_boosterParticlesEmitterRight1->SetEmissionDuration(0.1f);
	m_boosterParticlesEmitterRight1->SetStartColor(math::Vector4(1.0f, 0.3f, 0.0f, 1.0f));
	m_boosterParticlesEmitterRight1->SetEndColor(math::Vector4(1.0f, 1.0f, 0.0f, 0.5f));
	m_boosterParticlesEmitterRight1->SetMaxSpeed(20.0f);
	m_boosterParticlesEmitterRight1->SetMinSpeed(13.0f);
	m_boosterParticlesEmitterRight1->SetMaxSize(0.8f);
	m_boosterParticlesEmitterRight1->SetMinSize(0.4f);
	m_boosterParticlesEmitterRight1->SetEndSize(0.0f);
	m_boosterParticlesEmitterRight1->SetMaxLifeTime(0.25f);
	m_boosterParticlesEmitterRight1->SetMinLifeTime(0.15f);
	m_boosterParticlesEmitterRight1->SetRotationSpeed(10.0f);
	m_boosterParticlesEmitterRight1->SetRadius(2.2f);
	m_boosterParticlesEmitterRight1->SpawnAtSphereEdge(true);
	m_boosterParticlesEmitterRight1->SetSpread(2.7f);

	m_boosterParticlesEmitterRight2 = AddComponent<component::ParticleEmitterComponent>();
	m_boosterParticlesEmitterRight2->SetTexture("../res/textures/fire2.png");
	m_boosterParticlesEmitterRight2->SetShader("particleShader");
	m_boosterParticlesEmitterRight2->SetEmissionRate(5000);
	m_boosterParticlesEmitterRight2->SetEmissionDuration(0.1f);
	m_boosterParticlesEmitterRight2->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	m_boosterParticlesEmitterRight2->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
	m_boosterParticlesEmitterRight2->SetMaxSpeed(10.0f);
	m_boosterParticlesEmitterRight2->SetMinSpeed(6.0f);
	m_boosterParticlesEmitterRight2->SetMaxSize(0.6f);
	m_boosterParticlesEmitterRight2->SetMinSize(0.3f);
	m_boosterParticlesEmitterRight2->SetEndSize(0.0f);
	m_boosterParticlesEmitterRight2->SetMaxLifeTime(0.8f);
	m_boosterParticlesEmitterRight2->SetMinLifeTime(0.3f);
	m_boosterParticlesEmitterRight2->SetRotationSpeed(2.0f);
	m_boosterParticlesEmitterRight2->SetSpread(2.5f);

	//Rigidbody init
	m_rigidBody->SetMass(mass);
	m_rigidBody->SetCollider(new btBoxShape(btVector3(3, 20, 8)));
	m_rigidBody->setSleepingThresholds(0.2, 0.5);
	m_rigidBody->setGravity(btVector3(0, -15, 0));
	m_treasure = 300;


	//model
	m_modelIndex = 0;
	m_renderer->SetModel("testModel0");
	m_moving = false;
	//sound
	m_boostSound->SetClip("fFlames");
	m_boostSound->SetVolume(1000);
	m_soundDelay = 5;
	m_soundDelayLeft = 5;
	//movement
	m_speed = 70;
	m_turnSpeed = 20;
	m_roof = 1000000.0;
	m_flyCost = 20;

	//controlls/camera
	m_controlSensitivity = 0.13f;
	m_startUpSequence = true;
	m_elevateCamSpeed = 38;
	m_camZoomSpeed = 45.0f;
	m_camRotationSpeed = 2.0f;
	m_camMinDistanceFromBoat = 100.0f;
	m_camMaxDistanceFromBoat = 220.0f;
	m_cameraDistance = 50.0;
	m_aimDistance = 20;
	m_health = 100;
	m_armor = 0;
	m_maxHealth = m_health;
	m_maxArmor = 100;

	m_spawnedWormhole = false;
	m_aiming = false;
}
bool Ship::GetFreeCamera()
{
	return m_freeCamera;
}
void Ship::ShipMove(float const dt)
{
	//ship controls
	if (Input::GetButton(Input::Buttons::RT) || (!m_freeCamera && Input::GetKey(Input::Keys::W)) || (m_freeCamera && Input::GetKey(Input::Keys::Up)))
	{
		math::Vector3 forward = m_transform->Forward();

		//Remove y part;
		forward.y = 0;
		m_moving = true;
		m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed*m_rigidBody->GetMass()));
	}
}
void Ship::ShipRotate(float const dt)
{
	float turnDelta = 0;

	//For XBOX
	if (Input::GetLeftStickX())
		turnDelta = -Input::GetLeftStickX();

	//For Keyboard
	else if (!m_freeCamera)
	{
		if (Input::GetKey(Input::Keys::D))
			turnDelta = -Input::GetKey(Input::Keys::D);
		else if (-Input::GetKey(Input::Keys::A))
			turnDelta = Input::GetKey(Input::Keys::A);
	}

	//For Keyboard when freeCam is active
	else if (m_freeCamera)
	{
		if (Input::GetKey(Input::Keys::Right))
			turnDelta = -Input::GetKey(Input::Keys::Right);
		else if (Input::GetKey(Input::Keys::Left))
			turnDelta = Input::GetKey(Input::Keys::Left);
	}

	math::Vector3 right = m_transform->Right();

	//Remove y part;
	right.y = 0;
	m_rigidBody->activate();
	if (!m_moving)
		turnDelta *= 2;
	m_rigidBody->applyTorque(btVector3(0, m_turnSpeed*turnDelta*m_rigidBody->GetMass(), 0));

	if (abs(turnDelta) > 0.02)
		m_turning = true;
}
void Ship::ShipFly(float const upFactorPitch, float const upFactorRoll, float const left_y, float const dt)
{
	if ((Input::GetButton(Input::Buttons::LT) || Input::GetKey(Input::Keys::Space) || Input::GetKey(Input::Keys::LeftShift)) && m_treasure > m_flyCost)//Goes in even when m_treasure < m_flyCost * dt
	{
		m_treasure -= m_flyCost*dt;
		math::Vector3 forward = m_transform->Forward();
		m_moving = true;
		forward.y = 0;
		m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * 2 * m_speed*m_rigidBody->GetMass()));
		float turnDelta = -Input::GetLeftStickY();

		/*m_rigidBody->applyForce(btVector3(0, turnDelta*m_flyTurnSpeed*dt*m_rigidBody->GetMass(), 0), btVector3(0,0,8));
		btVector3 angular = m_rigidBody->getAngularVelocity();
		m_rigidBody->setAngularVelocity(btVector3(angular.x(), angular.y(), 0));*/
		m_flying = true;

	}
}
void Ship::ShipFireCannons()
{
}


void Ship::Aim(float side, math::Vector2 aimPos)
{
	m_aiming = true;
	CameraZoom(Time::GetDeltaTime());
	math::Vector3 lookAtPoint = math::Vector3(aimPos.x, 0, aimPos.y);
	//Recalculate look at point and the new distance from cam to ship
	m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
	math::Vector3 const distanceVector = lookAtPoint - m_cameraObject->m_transform->GetPosition();

	m_lookAtOffset = math::Vector3(0, (distanceVector.Length() / 4) + 5, 0);//recalculate lookatoffset depending on camera range from boat

	
	//Move camera "distance" away from boat.
	/*math::Vector3 newPos = m_lookAtPoint - (m_cameraObject->m_transform->Forward()*distance);

	newPos = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), newPos, dt*2.5);*/

	//m_cameraObject->m_transform->SetPosition(newPos);

	//move camera behind boat
	float distToTarget = math::Vector2(math::Vector2(m_transform->GetPosition().x, m_transform->GetPosition().y) - lookAtPoint).Length();
	math::Vector3 posBehindBoat = m_transform->GetPosition() + (side*m_transform->Right()*m_cameraDistance);
	posBehindBoat += (side*m_transform->Right()*distToTarget / 8);
	posBehindBoat.y = 35;
	posBehindBoat += (math::Vector3::Up*distToTarget / 8);
	posBehindBoat += (m_transform->Forward()*distToTarget / 8);
	posBehindBoat = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), posBehindBoat, Time::GetDeltaTime() * 2);

	m_cameraObject->m_transform->SetPosition(posBehindBoat);

	m_cameraObject->m_transform->SetRotation(0, 0, 0); //reset rotation
	m_cameraObject->m_transform->LookAt(lookAtPoint);//reset to planar orientation of camera with lookat

	math::Vector3 newPos = lookAtPoint - (m_cameraObject->m_transform->Forward()*m_cameraDistance);

	newPos = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), newPos, Time::GetDeltaTime()*2.5);
}

void Ship::ShipAimCannons()
{
	if (Input::GetButtonDown(Input::Buttons::RB))
	{
		m_aimRight = !m_aimRight;
		m_aimLeft = false;
	}
	else if(Input::GetButtonDown(Input::Buttons::LB))
	{
		m_aimLeft = !m_aimLeft;
		m_aimRight = false;
	}

	if (m_aimRight) //RIGHT
	{
		float deltaX = Input::GetRightStickY();
		m_aimDistance += deltaX*Time::GetDeltaTime() * 70;
		m_aimDistance = min(400, max(m_aimDistance, 100));
		math::Vector3 flatRight = m_transform->Right();
		flatRight.y = 0;
		flatRight.Normalize();
		math::Vector2 flatRight2D = math::Vector2(flatRight.x, flatRight.z);
		math::Vector2 target = math::Vector2(m_transform->GetPosition().x, m_transform->GetPosition().z) - flatRight2D*m_aimDistance;
		Aim(1, target);
		float angle = m_broadSideLeft->CalculateCanonAngle(math::Vector3(target.x, 0, target.y));

		if (angle > -500.0)
		{
			m_broadSideLeft->SetCanonAngle(-angle);

			m_waterObject->UpdateAim(math::Vector2(m_transform->GetPosition().x, m_transform->GetPosition().z), target);
		}

		if (Input::GetButtonDown(Input::Buttons::A) && m_treasure >= 50 && m_broadSideLeft->CanFire())
		{
			Input::Vibrate(0.0, 0.5, 0.5);
			m_broadSideLeft->Fire(); //Temporary fix
			m_treasure -= 50;
		}
	}

	else if (m_aimLeft) //LEFT
	{
		float deltaX = Input::GetRightStickY();
		
		m_aimDistance += deltaX*Time::GetDeltaTime()*70;
		m_aimDistance = min(400, max(m_aimDistance, 100));
		math::Vector3 flatRight = m_transform->Right();
		flatRight.y = 0;
		flatRight.Normalize();
		math::Vector2 flatRight2D = math::Vector2(flatRight.x, flatRight.z);
		math::Vector2 target = math::Vector2(m_transform->GetPosition().x, m_transform->GetPosition().z) + flatRight2D*m_aimDistance;
		Aim(-1, target);
		float angle = m_broadSideLeft->CalculateCanonAngle(math::Vector3(target.x, 0, target.y));

		if (angle > -500.0)
		{
			m_broadSideRight->SetCanonAngle(-angle);

			m_waterObject->UpdateAim(math::Vector2(m_transform->GetPosition().x, m_transform->GetPosition().z), target);
		}
		if (Input::GetButtonDown(Input::Buttons::A) && m_treasure >= 50 && m_broadSideRight->CanFire())
		{
			m_treasure -= 50;
			Input::Vibrate(0.5, 0, 0.5);
			m_broadSideRight->Fire(); //Temporary fix
		}
			

	}

	if (!m_aimLeft && !m_aimRight)
	{
		m_lookAtOffset = math::Vector3(0, 20, 0);
		m_aiming = false;
		m_waterObject->DisableAim();
	}

	//if (Input::GetKeyDown(Input::Keys::R) && m_counter == 5)
	//{
	//	/*int delay = 0;

	//	for (int i = 0; i < 40000; i++)
	//	{
	//		delay += 1;
	//	}*/

	//	m_counter = 0;
	//	
	//}
}
void Ship::UpgradeSpeed(float speedIncrease)
{
	m_speed = m_speed + speedIncrease;
}
void Ship::CameraRotate(float const right_x, float const right_y, float const dt, math::Vector3 const distanceVector)
{
	m_cameraObject->m_transform->Translate(distanceVector);//move camera into the boat to make rotations for the camera!
	if (std::abs(right_x) > m_controlSensitivity || std::abs(right_y) > m_controlSensitivity)
	{
		float angle = std::acos(m_cameraObject->m_transform->Forward().Dot(math::Vector3(0, 1, 0))) * 180 / math::PI;

		bool allowRotation = true;

		if (angle > 160)
		{
			if (right_y > 0)
			{
				allowRotation = false;
			}
		}
		else if (angle < 85)
		{
			if (right_y < 0)
			{
				allowRotation = false;
			}
		}

		if (allowRotation)//anti gimballock
		{
			m_cameraObject->m_transform->Rotate(m_camRotationSpeed * right_x * dt, 0, 0);
			m_cameraObject->m_transform->Rotate(0, m_cameraObject->m_transform->Forward().Dot(math::Vector3(0, 0, 1)) * m_camRotationSpeed * right_y * dt, m_cameraObject->m_transform->Forward().Dot(math::Vector3(-1, 0, 0)) * m_camRotationSpeed * right_y * dt);//rotate camera around the boat
		}
	}

	m_cameraObject->m_transform->Translate(-m_cameraObject->m_transform->Forward() * distanceVector.Length());//move the camera back to the distance it was, after rotations
}
void Ship::CameraZoom(float const dt)
{
	if (Input::GetButton(Input::Buttons::DPAD_UP) || Input::GetKey(Input::Keys::Z))
	{
		m_cameraDistance -= m_camZoomSpeed*dt;
	}

	if (Input::GetButton(Input::Buttons::DPAD_DOWN) || Input::GetKey(Input::Keys::X))
	{
		m_cameraDistance += m_camZoomSpeed*dt;
	}

	if (m_cameraDistance > m_camMaxDistanceFromBoat)
		m_cameraDistance = m_camMaxDistanceFromBoat;

	if (m_cameraDistance < m_camMinDistanceFromBoat)
		m_cameraDistance = m_camMinDistanceFromBoat;
}
void Ship::PlunderIsland()
{
	m_treasure += m_terrainObject->Plunder(m_transform->GetPosition());
}
int Ship::GetTreasure()
{
	return m_treasure + 0.5;
}
void Ship::Float(float dt)
{
	float waveHeight = 0;
	math::Vector3 bois;
	for (int i = 0; i < 12; i++)
	{

		if (i < 8)
		{
			waveHeight += m_floats[i]->UpdateBoat(m_rigidBody, m_moving);
			bois += m_floats[i]->m_transform->GetPosition();
		}
		else
		{
			m_floats[i]->UpdateBoat(m_rigidBody, m_moving);
		}

	}

	m_rigidBody->setDamping(0.0, 0.0);
	if (m_moving)
	{
		m_rigidBody->setDamping(0.5, 0.5);
	}
	if (m_turning)
		m_rigidBody->setDamping(0.3, 0.3);
	m_rigidBody->applyDamping(dt);


	bois /= 8;
	waveHeight /= 8;
	if (bois.y > waveHeight + m_roof && waveHeight > -10)
	{
		btVector3& v = m_rigidBody->getWorldTransform().getOrigin();
		float oldY = v.getY();
		float newY = waveHeight + m_roof;
		newY = oldY + dt*4.0 * (newY - oldY);
		v.setY(newY);
	}
	else if (bois.y < waveHeight && m_startUpSequence)
	{
		m_roof = 1.0f;
		m_startUpSequence = false;
		//m_cameraObject->m_transform->SetPosition(m_transform->GetPosition() + m_transform->Forward() * 200 + math::Vector3(0, 25, 0));
		m_lookAtOffset = math::Vector3(0, 20, 0);
		m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
		m_cameraObject->m_transform->LookAt(m_lookAtPoint);
	}
}
void Ship::Update()
{
	float const dt = Time::GetDeltaTime();


	if (m_startUpSequence)
	{
		m_boosterParticlesEmitterLeft1->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f + m_transform->Right() * 6.66f);
		m_boosterParticlesEmitterLeft1->SetDirection(m_transform->Forward());
		m_boosterParticlesEmitterLeft1->StartEmitting();
		m_boosterParticlesEmitterLeft2->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f + m_transform->Right() * 6.66f);
		m_boosterParticlesEmitterLeft2->SetDirection(m_transform->Forward());
		m_boosterParticlesEmitterLeft2->StartEmitting();
		m_boosterParticlesEmitterRight1->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f + m_transform->Right() * -6.66f);
		m_boosterParticlesEmitterRight1->SetDirection(m_transform->Forward());
		m_boosterParticlesEmitterRight1->StartEmitting();
		m_boosterParticlesEmitterRight2->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f + m_transform->Right() * -6.66f);
		m_boosterParticlesEmitterRight2->SetDirection(m_transform->Forward());
		m_boosterParticlesEmitterRight2->StartEmitting();
		m_boostSound->Play();
		Float(dt);
		return;
	}

	float right_x = Input::GetRightStickX();
	float right_y = Input::GetRightStickY();
	float left_x = Input::GetLeftStickX(); //not used?
	float left_y = Input::GetLeftStickY(); //not used?

	//If cam changed with arrow keys
	if (Input::GetKey(Input::Keys::Right))
		right_x = -Input::GetKey(Input::Keys::Right);
	else if (Input::GetKey(Input::Keys::Left))
		right_x = Input::GetKey(Input::Keys::Left);

	if (Input::GetKey(Input::Keys::Up))
		right_y = Input::GetKey(Input::Keys::Up);
	else if (Input::GetKey(Input::Keys::Down))
		right_y = -Input::GetKey(Input::Keys::Down);

	//get forward, right and up contrib
	float forwardFactor = 0; //not used?
	float rightFactor = -left_x; //not used?
	float upFactorPitch = m_transform->Forward().Dot(math::Vector3(0, 0, -1)) * left_y;
	float upFactorRoll = m_transform->Forward().Dot(math::Vector3(1, 0, 0)) * left_y;

	m_modelIndex = ((m_modelIndex + 1) % 3) + 1;

	//ShipBoost(dt);

	if (!m_freeCamera && !m_aiming)
	{
		CameraZoom(dt);

		//Recalculate look at point and the new distance from cam to ship
		m_lookAtPoint = m_transform->GetPosition() + m_lookAtOffset;
		math::Vector3 const distanceVector = m_lookAtPoint - m_cameraObject->m_transform->GetPosition();

		m_lookAtOffset = math::Vector3(0, (distanceVector.Length() / 4) + 5, 0);//recalculate lookatoffset depending on camera range from boat

		CameraRotate(right_x, right_y, dt, distanceVector);

		//Move camera "distance" away from boat.
		/*math::Vector3 newPos = m_lookAtPoint - (m_cameraObject->m_transform->Forward()*distance);

		newPos = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), newPos, dt*2.5);*/

		//m_cameraObject->m_transform->SetPosition(newPos);

		//move camera behind boat
		math::Vector3 posBehindBoat = m_lookAtPoint + (m_transform->Forward()*m_cameraDistance);
		posBehindBoat.y = 35;

		posBehindBoat = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), posBehindBoat, dt * 2);

		m_cameraObject->m_transform->SetPosition(posBehindBoat);

		m_cameraObject->m_transform->SetRotation(0, 0, 0); //reset rotation
		m_cameraObject->m_transform->LookAt(m_lookAtPoint);//reset to planar orientation of camera with lookat

		math::Vector3 newPos = m_lookAtPoint - (m_cameraObject->m_transform->Forward()*m_cameraDistance);

		newPos = math::Vector3::Lerp(m_cameraObject->m_transform->GetPosition(), newPos, dt*2.5);




		m_cameraObject->m_transform->SetPosition(newPos);
	}

	m_moving = false;
	m_flying = false;
	m_turning = false;

	//Ship Movement
	ShipMove(dt);
	ShipRotate(dt);
	ShipFly(upFactorPitch, upFactorRoll, left_y, dt);
	ShipFireCannons();
	ShipAimCannons();

	if (m_flying)
	{
		//Input::Vibrate(0.1, 0.1);
		//m_renderer->SetModel("testModel" + std::to_string(m_modelIndex));
		m_boosterParticlesEmitterLeft1->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f + m_transform->Right() * 6.66f);
		m_boosterParticlesEmitterLeft1->SetDirection(m_transform->Forward());
		m_boosterParticlesEmitterLeft1->StartEmitting();
		m_boosterParticlesEmitterLeft2->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f + m_transform->Right() * 6.66f);
		m_boosterParticlesEmitterLeft2->SetDirection(m_transform->Forward());
		m_boosterParticlesEmitterLeft2->StartEmitting();
		m_boosterParticlesEmitterRight1->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f + m_transform->Right() * -6.66f);
		m_boosterParticlesEmitterRight1->SetDirection(m_transform->Forward());
		m_boosterParticlesEmitterRight1->StartEmitting();
		m_boosterParticlesEmitterRight2->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f + m_transform->Right() * -6.66f);
		m_boosterParticlesEmitterRight2->SetDirection(m_transform->Forward());
		m_boosterParticlesEmitterRight2->StartEmitting();
		
		m_boostSound->Play();
	}
	else
	{
		//m_renderer->SetModel("testModel0");
		m_boostSound->Pause();
	}

	PlaySounds(dt);

	PlunderIsland();

	Float(dt);


	if (m_treasure > 500 && !m_spawnedWormhole)
	{
		Wormhole* wormhole = Instantiate<Wormhole>(math::Vector3(0,150,0),math::Quaternion::Identity,m_scene);
		wormhole->SetEndLevel(true);
		m_spawnedWormhole = true;
	}

	((WaterObject*)Find("WaterObject"))->SetOceanCenter(m_transform->GetPosition().x, m_transform->GetPosition().z);
}
void Ship::OnCollision(component::RigidBodyComponent* other)
{
	if (other->m_gameObject->GetType() == "Projectile")
	{
		Projectile* p = ((Projectile*)other->m_gameObject);
		if (p->m_spawnedBy == this)
			return;

		if (m_armor > 0)
		{
			m_armor -= p->GetDamageAmount();
			LOG("hit armor: " << m_armor);
		}
		else if (m_armor <= 0)
		{
			m_health -= p->GetDamageAmount();
			LOG("hit hp: " << m_health);
		}
	
		if (m_health <= 0)
		{
			LOG("You are dead!");
			Scene::LoadScene<MenuScene>();
		}

	}
}