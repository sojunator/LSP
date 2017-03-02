#pragma once
#include <Thomas.h>
#include "Broadside.h"
#include "../AI/AI.h"
#include "../../THOMAS/src/utils/DebugTools.h"
#include "ShipFloat.h"

using namespace thomas;
using namespace object;

class Enemy : public GameObject
{
private:

public:
	Enemy();

	void Start();
	void Move();
	void Rotate();
	void FireCannons();
	void Float(float dt);
	void Update();
	void OnCollision(component::RigidBodyComponent* other);
	void Die();


private:
	
	bool m_dead;
	//Objects
	ShipFloat* m_floats[12];
	Broadside* m_broadSideRight;
	Broadside* m_broadSideLeft;
	Broadside* m_broadSideRightCannonball;
	Broadside* m_broadSideLeftCannonball;
	Broadside* m_broadSideFront;

	//Components
	component::ParticleEmitterComponent* m_emitterSpark;
	component::ParticleEmitterComponent* m_emitterSmoke;
	component::RenderComponent* m_renderer;
	component::SoundComponent* m_sound;
	component::RigidBodyComponent* m_rigidBody;
	AI* m_ai;

	//Ship
	float m_health;
	bool m_moving;
	float m_mass;
	float m_maxSpeed;
	float m_speed;
	float m_accelerate;
	float m_retardation;
	float m_turnSpeed;
	int m_turnDir;
	int m_shootDir;

	math::Vector3 m_newForwardVec;

	float m_searchRadius;
	float m_attackRadius;

	bool m_islandForward;
	bool m_islandLeft;
	bool m_islandRight;

	//Sound
	float m_soundDelay;
	float m_soundDelayLeft;


	bool m_firstFrame;
};
