#include "Enemy.h"
#include "../../THOMAS/src/utils/DebugTools.h"

void Enemy::Start()
{
	m_firstFrame = true;
	m_mass = 20000;
	m_searchRadius = 1000;
	m_attackRadius = 200;
	m_turnDir = 0;
	m_shootDir = 0;
	m_newForwardVec = math::Vector3::Zero;

	m_islandForward = false;
	m_islandLeft = false;
	m_islandRight = false;

	m_soundDelay = 5;
	m_soundDelayLeft = 5;

	//Front
	m_floats[0] = Instantiate<ShipFloat>(math::Vector3(1.5, 0, 8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[1] = Instantiate<ShipFloat>(math::Vector3(-1.5, 0, 8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[0]->SetMass(0.10*m_mass);
	m_floats[1]->SetMass(0.10*m_mass);
	//front middle
	m_floats[2] = Instantiate<ShipFloat>(math::Vector3(3, 0, 5), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[3] = Instantiate<ShipFloat>(math::Vector3(-3, 0, 5), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[2]->SetMass(0.12*m_mass);
	m_floats[3]->SetMass(0.12*m_mass);
	//back middle
	m_floats[4] = Instantiate<ShipFloat>(math::Vector3(3, 0, -1), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[5] = Instantiate<ShipFloat>(math::Vector3(-3, 0, -1), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[4]->SetMass(0.13*m_mass);
	m_floats[5]->SetMass(0.13*m_mass);
	//back
	m_floats[6] = Instantiate<ShipFloat>(math::Vector3(2.5, 0, -8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[7] = Instantiate<ShipFloat>(math::Vector3(-2.5, 0, -8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[6]->SetMass(0.15*m_mass);
	m_floats[7]->SetMass(0.15*m_mass);

	//stabilizers front
	m_floats[8] = Instantiate<ShipFloat>(math::Vector3(2.5, 5, 8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[9] = Instantiate<ShipFloat>(math::Vector3(-2.5, 5, 8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[8]->SetMass(0.5*m_mass);
	m_floats[9]->SetMass(0.5*m_mass);
	//stabilizers back
	m_floats[10] = Instantiate<ShipFloat>(math::Vector3(2.5, 5, -8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[11] = Instantiate<ShipFloat>(math::Vector3(-2.5, 5, -8), math::Quaternion::Identity, m_transform, m_scene);
	m_floats[10]->SetMass(0.5*m_mass);
	m_floats[11]->SetMass(0.5*m_mass);

	//m_transform->SetPosition(0, 0.5, 0);

	m_renderer = AddComponent<component::RenderComponent>();
	m_sound = AddComponent<component::SoundComponent>();
	m_ai = AddComponent<AI>();
	m_rigidBody = AddComponent<component::RigidBodyComponent>();

	m_broadSideLeft = Instantiate<Broadside>(math::Vector3(-6, 8, 2.3), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToradians(270)), m_transform, m_scene);
	m_broadSideRight = Instantiate<Broadside>(math::Vector3(6, 8, -2.8), math::Quaternion::CreateFromAxisAngle(math::Vector3(0, 1, 0), math::DegreesToradians(90)), m_transform, m_scene);

	m_broadSideRight->CreateCannons();
	m_broadSideLeft->CreateCannons();


	m_renderer->SetModel("testModelEnemy");
	m_moving = false;


	//Rigidbody init
	m_rigidBody->SetMass(m_mass);
	m_rigidBody->SetCollider(new btBoxShape(btVector3(3, 12, 8)));
	m_rigidBody->setSleepingThresholds(0.2, 0.5);
	m_rigidBody->setGravity(btVector3(0, -15, 0));

	//Sound
	m_health = 20;
	m_dead = false;
	//Movement
	m_maxSpeed = 80;
	m_accelerate = 15;
	m_retardation = -20;
	m_speed = 0;
	m_turnSpeed = 25;
	m_changeSpeed = 0;

	//utils::DebugTools::AddBool(m_islandForward, "Island F");
	//utils::DebugTools::AddBool(m_islandRight, "Island R");
	//utils::DebugTools::AddBool(m_islandLeft, "Island L");
	thomas::utils::DebugTools::AddInteger(m_turnDir, "Turn Dir");

	m_emitterSpark = AddComponent<component::ParticleEmitterComponent>();
	m_emitterSpark->SetNrOfParticles(256 * 6 + 254);
	m_emitterSpark->SetTexture("../res/textures/spark.png");
	m_emitterSpark->SetShader("particleShader");
	m_emitterSpark->SetPosition(m_transform->GetPosition());
	m_emitterSpark->SetDirection(math::Vector3(0, 0, 1));
	m_emitterSpark->SetMaxDelay(0.0f);
	m_emitterSpark->SetMinDelay(0.0f);
	m_emitterSpark->SetMaxSpeed(20.0f);
	m_emitterSpark->SetMinSpeed(12.0f);
	m_emitterSpark->SetMaxSize(2.0f);
	m_emitterSpark->SetMinSize(1.0f);
	m_emitterSpark->SetMaxLifeTime(0.5f);
	m_emitterSpark->SetMinLifeTime(0.3f);
	m_emitterSpark->SetSpread(0.71f);

	m_emitterSmoke = AddComponent<component::ParticleEmitterComponent>();
	m_emitterSmoke->SetNrOfParticles(256 * 6 + 254);
	m_emitterSmoke->SetTexture("../res/textures/smokeParticle.png");
	m_emitterSmoke->SetShader("particleShader");
	m_emitterSmoke->SetPosition(m_transform->GetPosition());
	m_emitterSmoke->SetDirection(math::Vector3(0, 1, 0));
	m_emitterSmoke->SetMaxDelay(2.45f);
	m_emitterSmoke->SetMinDelay(0.15f);
	m_emitterSmoke->SetMaxSpeed(9.0f);
	m_emitterSmoke->SetMinSpeed(6.0f);
	m_emitterSmoke->SetMaxSize(3.2f);
	m_emitterSmoke->SetMinSize(2.4f);
	m_emitterSmoke->SetMaxLifeTime(3.55f);
	m_emitterSmoke->SetMinLifeTime(2.4f);
	m_emitterSmoke->SetSpread(0.8f);

}

void Enemy::Move()
{
	math::Vector3 forward = m_transform->Forward();
	forward.y = 0;		//Remove y so no flying
	m_moving = true;

	switch (m_ai->GetState())
	{
	case AI::Behavior::Attacking:
		//FireCannons();
		m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * m_rigidBody->GetMass()));
		Rotate();
		break;
	case AI::Behavior::Firing:
		//FireCannons();
		m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * m_rigidBody->GetMass()));
		Rotate();
		break;
	case AI::Behavior::Searching:
		m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * m_rigidBody->GetMass()));
		Rotate();
		break;
	case AI::Behavior::Idle:
		//Slow down and stop
		m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * m_rigidBody->GetMass()));
		Rotate();
		break;
	case::AI::Behavior::Dodge:
		m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * m_rigidBody->GetMass()));
		Rotate();
		break;
	default:
		break;
	}
}

void Enemy::Rotate()
{
	math::Vector3 right = m_transform->Right();
	right.y = 0;		//Remove y so no flying
	m_rigidBody->activate();



	float dir = m_newForwardVec.Dot(m_transform->Right());
	if (m_transform->Forward() != m_newForwardVec)
	{
		if (m_turnDir == 1)
			m_rigidBody->applyTorque(btVector3(0, -m_turnSpeed * m_rigidBody->GetMass(), 0));
		else if (m_turnDir == -1)
			m_rigidBody->applyTorque(btVector3(0, m_turnSpeed * m_rigidBody->GetMass(), 0));
	}
}

void Enemy::FireCannons()
{
	if (m_shootDir == 1)
	{

		math::Vector3 targetPos = m_ai->GetTargetPos();
		math::Vector2 target(targetPos.x, targetPos.z);
		float angle = m_broadSideRight->CalculateCanonAngle(math::Vector3(target.x, 0, target.y));

		if (angle > -500.0)
		{
			m_broadSideRight->SetCanonAngle(-angle);
			m_broadSideRight->Fire();
		}
	}

	else if (m_shootDir == -1)
	{
		math::Vector3 targetPos = m_ai->GetTargetPos();
		math::Vector2 target(targetPos.x, targetPos.z);
		float angle = m_broadSideLeft->CalculateCanonAngle(math::Vector3(target.x, 0, target.y));

		if (angle > -500.0)
		{
			m_broadSideLeft->SetCanonAngle(-angle);
			m_broadSideLeft->Fire();
		}
	}
}

void Enemy::Float(float dt)
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
	m_rigidBody->applyDamping(dt);


	bois /= 8;
	waveHeight /= 8;
	if (bois.y > waveHeight + 0.5)
	{
		btVector3& v = m_rigidBody->getWorldTransform().getOrigin();
		float oldY = v.getY();
		float newY = waveHeight + 0.5;
		newY = oldY + dt*4.0 * (newY - oldY);
		v.setY(newY);
	}
}

void Enemy::Update()
{
	float const dt = Time::GetDeltaTime();

	if (m_dead)
	{
		m_rigidBody->setDamping(0.5, 0.5);
		if (m_transform->GetPosition().y < -10)
			Destroy(this);
		return;
	}

	m_moving = false;

	m_ai->Escape();
	//Checked if at last known pos and if not found go idle
	m_ai->IdleTimer();
	m_ai->InsideRadius(m_searchRadius, m_transform->GetPosition(), m_newForwardVec);
	m_ai->InsideAttackRadius(m_attackRadius, m_transform->GetPosition(), m_newForwardVec);

	//Check for islands
	m_islandForward = m_ai->Collision(m_transform->GetPosition() + (-m_transform->Forward() * 60));	//Check island front
	m_islandRight = m_ai->Collision(m_transform->GetPosition() + (-m_transform->Right() * 30));	//Check island right
	m_islandLeft = m_ai->Collision(m_transform->GetPosition() - (-m_transform->Right() * 30));	//Check island left

	m_turnDir = m_ai->TurnDir(m_transform->GetPosition(), -m_transform->Forward(), -m_transform->Right(), m_islandForward, m_islandRight, m_islandLeft);
	m_shootDir = m_ai->FireCannons(m_transform->GetPosition(), -m_transform->Right());

	if (!m_firstFrame)
	{
		ChangeSpeed(dt);
		Move();
	}
	m_firstFrame = false;

	Float(dt);
}

void Enemy::OnCollision(component::RigidBodyComponent * other)
{
	if (other->m_gameObject->GetType() == "Projectile")
	{
		Projectile* p = ((Projectile*)other->m_gameObject);
		if (p->m_spawnedBy == this)
			return;
		m_health -= p->GetDamageAmount();
		if (m_health <= 0)
			Die();
	}

}

void Enemy::Die()
{
	m_dead = true;
	m_emitterSpark->SetDirection(m_transform->Up());
	m_emitterSmoke->SetDirection(m_transform->Up());
	m_emitterSmoke->StartEmitting();
	m_emitterSpark->StartEmitting();
	m_sound->PlayOneShot("fEnemyExplode", 0.7);
}

void Enemy::ChangeSpeed(float dt)
{
	float newSpeed = 0;

	if (m_ai->GetState() == AI::Behavior::Idle)
		newSpeed = m_speed + dt * m_retardation;
	else if (m_ai->GetState() == AI::Behavior::Searching || (m_ai->GetState() == AI::Behavior::Attacking && m_turnDir == 0))
		newSpeed = m_speed + dt * m_accelerate;
	else if (m_turnSpeed != 0)
		newSpeed = m_speed + dt * m_retardation;
	else
		newSpeed = m_speed + dt * m_accelerate;

	newSpeed = std::fmax(newSpeed, 30.0);
	newSpeed = std::fmin(newSpeed, m_maxSpeed);
	//m_speed = newSpeed;
	m_speed = m_maxSpeed;	//Don't forgett to remove
}

