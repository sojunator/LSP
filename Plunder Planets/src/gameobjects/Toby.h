#pragma once
#include "../AI/AI.h"
#include "Ship.h"
using namespace thomas;
using namespace object;
class Toby : public GameObject
{
private:

public:
	Toby() : GameObject("TobyEnemy")
	{
	}

	void Init(float difficulty)
	{
		float randVal = ((double)rand() / (RAND_MAX));
		m_health = 5 + difficulty * randVal * 5;
		m_speed = 300 + difficulty * randVal * 50;
		m_turnSpeed = 80 + difficulty * randVal * 5.5f;
		m_explosionDamage = 20 + difficulty * 10;
	}


	void Start()
	{
		m_explosionDelay = 4;
		m_mass = 500000;
		m_soundDelay = 5;
		m_soundDelayLeft = 5;
		m_roof = 0.5;
		m_timeLeftToActivateRoof = 0;
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

		m_renderer->SetModel("tobyEnemy0");
		m_swapDelay = 0;


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

		m_boosterParticlesEmitterMiddle1 = AddComponent<component::ParticleEmitterComponent>();
		m_boosterParticlesEmitterMiddle1->SetTexture("../res/textures/fire.png");
		m_boosterParticlesEmitterMiddle1->SetShader("particleShader");
		m_boosterParticlesEmitterMiddle1->SetEmissionRate(2500);
		m_boosterParticlesEmitterMiddle1->SetEmissionDuration(0.1f);
		m_boosterParticlesEmitterMiddle1->SetStartColor(math::Vector4(1.0f, 0.3f, 0.0f, 1.0f));
		m_boosterParticlesEmitterMiddle1->SetEndColor(math::Vector4(1.0f, 1.0f, 0.0f, 0.5f));
		m_boosterParticlesEmitterMiddle1->SetMaxSpeed(20.0f);
		m_boosterParticlesEmitterMiddle1->SetMinSpeed(13.0f);
		m_boosterParticlesEmitterMiddle1->SetMaxSize(0.8f);
		m_boosterParticlesEmitterMiddle1->SetMinSize(0.4f);
		m_boosterParticlesEmitterMiddle1->SetEndSize(0.0f);
		m_boosterParticlesEmitterMiddle1->SetMaxLifeTime(0.25f);
		m_boosterParticlesEmitterMiddle1->SetMinLifeTime(0.15f);
		m_boosterParticlesEmitterMiddle1->SetRotationSpeed(10.0f);
		m_boosterParticlesEmitterMiddle1->SetRadius(2.2f);
		m_boosterParticlesEmitterMiddle1->SpawnAtSphereEdge(true);
		m_boosterParticlesEmitterMiddle1->SetSpread(2.7f);
		m_boosterParticlesEmitterMiddle1->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f);
		m_boosterParticlesEmitterMiddle1->SetDirection(m_transform->Forward());

		m_boosterParticlesEmitterMiddle2 = AddComponent<component::ParticleEmitterComponent>();
		m_boosterParticlesEmitterMiddle2->SetTexture("../res/textures/fire2.png");
		m_boosterParticlesEmitterMiddle2->SetShader("particleShader");
		m_boosterParticlesEmitterMiddle2->SetEmissionRate(5000);
		m_boosterParticlesEmitterMiddle2->SetEmissionDuration(0.1f);
		m_boosterParticlesEmitterMiddle2->SetStartColor(math::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
		m_boosterParticlesEmitterMiddle2->SetEndColor(math::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
		m_boosterParticlesEmitterMiddle2->SetMaxSpeed(10.0f);
		m_boosterParticlesEmitterMiddle2->SetMinSpeed(6.0f);
		m_boosterParticlesEmitterMiddle2->SetMaxSize(0.6f);
		m_boosterParticlesEmitterMiddle2->SetMinSize(0.3f);
		m_boosterParticlesEmitterMiddle2->SetEndSize(0.0f);
		m_boosterParticlesEmitterMiddle2->SetMaxLifeTime(0.8f);
		m_boosterParticlesEmitterMiddle2->SetMinLifeTime(0.3f);
		m_boosterParticlesEmitterMiddle2->SetRotationSpeed(2.0f);
		m_boosterParticlesEmitterMiddle2->SetSpread(2.5f);
		m_boosterParticlesEmitterMiddle2->SetOffset(m_transform->Forward() * 10.45f + m_transform->Up() * 3.25f);
		m_boosterParticlesEmitterMiddle2->SetDirection(m_transform->Forward());
		
		m_explosionParticle1 = AddComponent<component::ParticleEmitterComponent>();
		m_explosionParticle1->ImportEmitter("../res/particles/tobyExplode1.thomasps");

		m_explosionSmokeParticle = AddComponent<component::ParticleEmitterComponent>();
		m_explosionSmokeParticle->ImportEmitter("../res/particles/tobysmoke.thomasps");

		m_swapDelay = 0;
		m_modelIndex = 0;

		m_frustumCullingComponent = AddComponent<component::FrustumCullingComponent>();
		m_frustumCullingComponent->SetRadius(15);
		m_frustumCullingComponent->SetPosition(m_transform->GetPosition());
		m_ai->SetFireRadius(500);
		m_sound->SetClip("fTobyTimer");
		m_sound->SetVolume(0.7);
		m_sound->SetLooping(false);

		
	}


	void Move(float dt)
	{
		if (m_ai->GetState() == AI::State::Chasing || m_ai->GetState() == AI::State::Searching || m_ai->GetState() == AI::State::Attacking)
		{
			math::Vector3 forward = m_transform->Forward();
			forward.y = 0;		//Remove y so no flying

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
			targetD.y = 0;
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

	void DisableRoof()
	{
		m_roof = 100000;
		m_timeLeftToActivateRoof = 1.0f;
	}

	void Float(float dt)
	{
		float waveHeight = 0;
		math::Vector3 bois;
		for (int i = 0; i < 12; i++)
		{

			if (i < 8)
			{
				waveHeight += m_floats[i]->UpdateBoat(m_rigidBody);
				bois += m_floats[i]->m_transform->GetPosition();
			}
			else
			{
				m_floats[i]->UpdateBoat(m_rigidBody);
			}

		}

		if (m_timeLeftToActivateRoof <= 0)
		{
			m_rigidBody->setDamping(0.9, 0.9);
			m_rigidBody->applyDamping(dt);
		}


		bois /= 8;
		waveHeight /= 8;
		if (bois.y > waveHeight + m_roof)
		{
			btVector3& v = m_rigidBody->getWorldTransform().getOrigin();
			float oldY = v.getY();
			float newY = waveHeight + m_roof;
			newY = oldY + dt*4.0 * (newY - oldY);
			v.setY(newY);
		}
		else if (bois.y < waveHeight)
		{
			if (m_timeLeftToActivateRoof <= 0)
				m_roof = 0.5f;
			else
				m_timeLeftToActivateRoof -= ThomasTime::GetDeltaTime();
		}
	}


	void Update()
	{

		if (m_hasExploded)
		{
			m_explode = false;
		}

		float const dt = ThomasTime::GetDeltaTime();
		if (m_dead)
		{
			m_rigidBody->setDamping(0.5, 0.5);
			m_deathTime -= dt;
			((EnemyManager*)Find("EnemyManager"))->RemoveEnemy(EnemyManager::EnemyTypes::TOBY);
			if (m_deathTime < 0)//m_transform->GetPosition().y < -10)
				Destroy(this);
			return;
		}

		m_boosting = false;

		if (!m_ai->GetActive())
		{
			if (thomas::object::GameObject::Find("Ship"))
			{
				m_ai->SetActive(true);
			}
		}
		else
		{
			
			Rotate(dt);
			Move(dt);

			if (m_boosting)
			{
				m_sound->Play();
				//Input::Vibrate(0.1, 0.1);
				//m_renderer->SetModel("testModel" + std::to_string(m_modelIndex));
				m_boosterParticlesEmitterMiddle1->StartEmitting();
				m_boosterParticlesEmitterMiddle2->StartEmitting();


				m_explosionDelay -= ThomasTime::GetDeltaTime();
				m_swapDelay -= ThomasTime::GetDeltaTime();

				if (m_swapDelay <= 0)
				{
					m_modelIndex = (m_modelIndex + 1) % 2;
					if (m_explosionDelay > 0.5)
					{
						float l = 1-(m_explosionDelay/4.0);
						m_swapDelay = 0;
						m_swapDelay = (0.5 * (1.0f - l)) + (0.0 * l);
					}
					else if (m_explosionDelay > 0.0)
					{
						m_swapDelay = 0;
						m_modelIndex = 1;
					}
					
					m_renderer->SetModel("tobyEnemy" + std::to_string(m_modelIndex));
				}

				
				
			}

		}

		if (m_explosionDelay <= 0)
			Die();

		Float(dt);
	}

	void TakeDamage(float dmg)
	{
		m_sound->PlayOneShot("fSmallExplosion", 0.7);
		m_health -= dmg;
		if (m_health <= 0)
			Die();
	}

	void OnCollision(component::RigidBodyComponent::Collision collision)
	{
		if (collision.otherRigidbody->m_gameObject->GetType() == "Projectile" && collision.thisRigidbody == m_rigidBody &!m_dead)
		{
			Projectile* p = ((Projectile*)collision.otherRigidbody->m_gameObject);
			if (p->m_spawnedBy != this)
			{
				TakeDamage(p->GetDamageAmount());
				Destroy(p);
			}
				
		}
		else if (collision.thisRigidbody == m_explosionCollider && collision.otherRigidbody != m_rigidBody && m_explode)
		{
			math::Vector3 impulseVector = collision.otherRigidbody->m_gameObject->m_transform->GetPosition() - m_transform->GetPosition();
			float distanceFromCenter = impulseVector.Length();
			float dmgModifier = 1-(distanceFromCenter / m_explosionRadius);
			impulseVector.Normalize();
			impulseVector.y = 0.06;
			collision.otherRigidbody->applyCentralImpulse(Physics::ToBullet(impulseVector)*collision.otherRigidbody->GetMass() * dmgModifier * 150);
			if(collision.otherRigidbody->m_gameObject->GetType() == "TobyEnemy")
			{
				m_hasExploded = true;
				Toby* tobyEnemy = (Toby*)collision.otherRigidbody->m_gameObject;
				tobyEnemy->TakeDamage(dmgModifier*m_explosionDamage);
				tobyEnemy->DisableRoof();
			}
			else if (collision.otherRigidbody->m_gameObject->GetType() == "Ship")
			{
				m_hasExploded = true;
				Ship* player = (Ship*)collision.otherRigidbody->m_gameObject;
				player->TakeDamage(dmgModifier*m_explosionDamage);
				player->DisableRoof();
			}
			else if (collision.otherRigidbody->m_gameObject->GetType() == "BasicEnemy")
			{

				BasicEnemy* basicEnemy = (BasicEnemy*)collision.otherRigidbody->m_gameObject;
				basicEnemy->TakeDamage(dmgModifier*m_explosionDamage);
				basicEnemy->DisableRoof();
			}


		}
		else if (collision.thisRigidbody == m_rigidBody && collision.otherRigidbody->m_gameObject->GetType() == "Ship" && !m_dead)
		{
			Die();
		}

	}


	void Die()
	{
		m_sound->Pause();
		m_dead = true;
		m_explode = true;
		m_hasExploded = false;
		m_sound->PlayOneShot("fTobyExplode", 0.7);
		m_explosionParticle1->StartEmitting();
		m_explosionSmokeParticle->StartEmitting();
		m_renderer->SetActive(false);
		m_rigidBody->SetActive(false);
	}

public:
	component::RigidBodyComponent* m_explosionCollider;
private:


	float m_deathTime;
	bool m_dead;
	bool m_hasExploded;
	//Objects
	ShipFloat* m_floats[12];
	//ShipStats* m_shipStats = new ShipStats(1);

	//Components
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	component::RigidBodyComponent* m_rigidBody;
	
	component::FrustumCullingComponent* m_frustumCullingComponent;

	component::ParticleEmitterComponent* m_explosionSmokeParticle;
	component::ParticleEmitterComponent* m_explosionParticle1;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterMiddle1;
	component::ParticleEmitterComponent* m_boosterParticlesEmitterMiddle2;

	AI* m_ai;

	//Ship
	float m_health;
	float m_mass;
	float m_speed;
	float m_turnSpeed;
	bool m_boosting;
	bool m_explode;
	float m_explosionRadius;
	float m_explosionDamage;
	//Sound
	float m_soundDelay;
	float m_soundDelayLeft;
	int m_modelIndex;
	float m_explosionDelay;
	float m_swapDelay;
	float m_roof;
	float m_timeLeftToActivateRoof;
};
