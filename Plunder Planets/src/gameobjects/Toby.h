#pragma once


#include <Thomas.h>
#include "../AI/AI.h"
#include "../../THOMAS/src/utils/DebugTools.h"
#include "ShipStats.h"


using namespace thomas;
using namespace object;
class Toby : public GameObject
{
private:

public:
	Toby() : GameObject("TobyEnemy")
	{
	}

	void Start()
	{
		m_mass = 500000;
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
		m_ai->SetActive(false);
		m_rigidBody = AddComponent<component::RigidBodyComponent>();

		m_renderer->SetModel("testModelEnemy");
		m_moving = false;


		//Rigidbody init
		m_rigidBody->SetMass(m_mass);
		m_rigidBody->SetCollider(new btBoxShape(btVector3(3, 12, 8)));
		m_rigidBody->setSleepingThresholds(0.2, 0.5);
		m_rigidBody->setGravity(btVector3(0, -15, 0));


		m_explosionRadius = 50;
		m_explosionCollider = AddComponent<component::RigidBodyComponent>();
		m_explosionCollider->SetCollider(new btSphereShape(m_explosionRadius));
		m_explosionCollider->SetKinematic(true);
		m_explosionCollider->setCollisionFlags(m_explosionCollider->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

		//Sound
		m_health = 20;
		m_dead = false;
		m_deathTime = 2;
		//Movement
		m_speed = 200;
		m_turnSpeed = 50;

		//utils::DebugTools::AddBool(m_islandForward, "Island F");
		//utils::DebugTools::AddBool(m_islandRight, "Island R");
		//utils::DebugTools::AddBool(m_islandLeft, "Island L");

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



		m_explosionParticle = AddComponent<component::ParticleEmitterComponent>();
		m_explosionParticle->SetTexture("../res/textures/fire2.png");
		m_explosionParticle->SetLooping(true);
		m_explosionParticle->AddToDebugMenu();

		m_frustumCullingComponent = AddComponent<component::FrustumCullingComponent>();
		m_frustumCullingComponent->SetRadius(15);
		m_frustumCullingComponent->SetPosition(m_transform->GetPosition());
	}


	void Move(float dt)
	{
		if (m_ai->GetState() == AI::State::Chasing || m_ai->GetState() == AI::State::Searching || m_ai->GetState() == AI::State::Attacking)
		{
			math::Vector3 forward = m_transform->Forward();
			forward.y = 0;		//Remove y so no flying
			m_moving = true;

			float dir = calcDir();

			float moveSpeed = 1 - abs(dir);

			if (m_ai->GetState() == AI::State::Attacking)
			{
				m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * 2.0 * m_rigidBody->GetMass() * moveSpeed));
				m_boosting = true;
			}
			else
			{
				m_rigidBody->applyCentralForce(*(btVector3*)&(-forward * m_speed * m_rigidBody->GetMass() * moveSpeed));
			}



		}

	}

	void Rotate(float dt)
	{

		if (m_ai->GetState() == AI::State::Chasing || m_ai->GetState() == AI::State::Searching || m_ai->GetState() == AI::State::Attacking)
		{

			float dir = calcDir();

			m_rigidBody->applyTorque(btVector3(0, m_turnSpeed * m_rigidBody->GetMass() * dir, 0));

		}

	}


	float calcDir()
	{
		if (m_ai->GetState() == AI::State::Chasing || m_ai->GetState() == AI::State::Searching ||m_ai->GetState() == AI::State::Attacking)
		{
			math::Vector3 forward = m_transform->Forward();
			forward.y = 0;		//Remove y so no flying
			m_rigidBody->activate();
			math::Vector3 targetD = m_ai->GetMovePos() - m_transform->GetPosition();
			targetD.Normalize();

			float dir = AngleDir(-forward, targetD, math::Vector3::Up);

			return dir;
		}
	}

	float AngleDir(math::Vector3 fwd, math::Vector3 targetDir, math::Vector3 up)
	{
		math::Vector3 perp = fwd.Cross(targetDir);
		float dir = perp.Dot(up);
		return dir;
	}

	void Float(float dt)
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


	void Update()
	{
		m_explosionParticle->StartEmitting();
		float const dt = ThomasTime::GetDeltaTime();

		if (m_dead)
		{
			m_rigidBody->setDamping(0.5, 0.5);
			m_deathTime -= dt;
			if (m_deathTime < 0)//m_transform->GetPosition().y < -10)
				Destroy(this);
			return;
		}

		m_boosting = false;

		if (!m_ai->GetActive())
		{
			if (thomas::object::GameObject::Find("Ship"))
			{
				//m_ai->SetActive(true);
			}
		}
		else
		{
			Rotate(dt);
			Move(dt);

			if (m_boosting)
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
			}

		}

		Float(dt);
	}

	void OnCollision(component::RigidBodyComponent::Collision collision)
	{
		if (collision.otherRigidbody->m_gameObject->GetType() == "Projectile" && collision.thisRigidbody == m_rigidBody)
		{
			Projectile* p = ((Projectile*)collision.otherRigidbody->m_gameObject);
			if (p->m_spawnedBy == this)
				return;
			m_health -= p->GetDamageAmount();
			if (m_health <= 0)
				Die();
		}
		else if (collision.thisRigidbody == m_explosionCollider && collision.otherRigidbody != m_rigidBody && m_explode)
		{
			math::Vector3 impulseVector = collision.otherRigidbody->m_gameObject->m_transform->GetPosition() - m_transform->GetPosition();
			float distanceFromCenter = impulseVector.Length();
			float dmgModifier =  1-(distanceFromCenter / m_explosionRadius);
			impulseVector.Normalize();
			collision.otherRigidbody->applyCentralImpulse(Physics::ToBullet(impulseVector)*collision.otherRigidbody->GetMass() * dmgModifier);
		}
		else if (collision.thisRigidbody == m_rigidBody && collision.otherRigidbody->m_gameObject->GetType() == "Ship")
		{
			Die();
		}
		


	}

	void Die()
	{
		m_dead = true;
		m_explode = true;
		m_sound->PlayOneShot("fEnemyExplode", 0.7);
	}

private:

	float m_deathTime;
	bool m_dead;
	//Objects
	ShipFloat* m_floats[12];
	Broadside* m_broadSideRight;
	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRightCannonball;
	Broadside* m_broadSideLeftCannonball;
	Broadside* m_broadSideFront;
	//ShipStats* m_shipStats = new ShipStats(1);

	//Components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	component::RigidBodyComponent* m_rigidBody;
	component::RigidBodyComponent* m_explosionCollider;
	component::FrustumCullingComponent* m_frustumCullingComponent;

	component::ParticleEmitterComponent* m_explosionParticle;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterRight1;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterRight2;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterLeft1;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterLeft2;

	AI* m_ai;

	//Ship
	float m_health;
	float m_mass;
	float m_speed;
	float m_turnSpeed;
	bool m_boosting;
	bool m_moving;
	bool m_explode;
	float m_explosionRadius;

	//Sound
	float m_soundDelay;
	float m_soundDelayLeft;
};
