#pragma once

#include <Thomas.h>


using namespace thomas;
using namespace object;
class GoldEmitterObject : public GameObject
{

private:

public:
	GoldEmitterObject() : GameObject("GoldEmitterObject")
	{

	};

	void Start()
	{
		m_goldEmitter = thomas::object::GameObject::AddComponent<thomas::object::component::ParticleEmitterComponent>();
		m_goldEmitter->ImportEmitter("../res/textures/goldemission.thomasps");

	};



	void Update()
	{

	};
		
	void StartEmittingParticles(math::Vector3 dir)
	{
		m_goldEmitter->SetDirection(dir);
		m_goldEmitter->StartEmitting();
	}

	void StopEmittingParticles()
	{
		m_goldEmitter->StopEmitting();
		
	}
private:
	thomas::object::component::ParticleEmitterComponent* m_goldEmitter;
};