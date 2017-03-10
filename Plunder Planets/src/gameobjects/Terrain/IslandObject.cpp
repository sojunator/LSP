#include "IslandObject.h"
#include "../PauseObjectMenuObject.h"

thomas::object::component::SoundComponent* IslandObject::m_sound;

IslandObject::~IslandObject()
{
}

void IslandObject::Start()
{
	m_frustrumCullingComponent = AddComponent<thomas::object::component::FrustumCullingComponent>();
	m_renderer = thomas::object::GameObject::AddComponent<thomas::object::component::RenderComponent>();
	m_sound = thomas::object::GameObject::AddComponent<thomas::object::component::SoundComponent>();
	m_goldEmitter = thomas::object::GameObject::AddComponent<thomas::object::component::ParticleEmitterComponent>();
	m_goldEmitter->ImportEmitter("../res/textures/goldemission.thomasps");
	m_goldEmitter->StopEmitting();
	m_smokeEmitter = thomas::object::GameObject::AddComponent<thomas::object::component::ParticleEmitterComponent>();
	m_sound->SetClip("fPlunder");
	m_sound->SetLooping(true);
	m_falling = false;
	m_destroy = false;
	m_pauseObj = nullptr;
}

void IslandObject::Update()
{
	btVector3 posRigid = m_rigidBody->getWorldTransform().getOrigin();
	thomas::math::Vector3 posTran = m_transform->GetPosition();
	if (m_falling)
	{
		if (m_rigidBody->getWorldTransform().getOrigin().getY() <= -800)
		{
			m_destroy = true;
		}
	}
	if (!m_pauseObj)
	{
		m_pauseObj = (PauseObjectMenuObject*)Find("PauseObjectMenuObject");
	}
}

void IslandObject::SetModel(int island)
{
	m_renderer->SetModel("Island-" + std::to_string(island));
}

void IslandObject::SinkIsland()
{
	if (!m_falling)
	{
		m_rigidBody->SetKinematic(false);
		m_rigidBody->SetMass(8000000);
		m_rigidBody->activate();
		m_falling = true;
		m_smokeEmitter->StartEmitting();
	}
}

void IslandObject::Looting(bool gotLoot)
{
	if (gotLoot && !m_pauseObj->GetPauseState())
	{
		m_sound->Play();
		
		m_goldEmitter->StartEmitting();
	}
	else
	{
		m_sound->Pause();
		m_goldEmitter->StopEmitting();
	}
}

void IslandObject::PlaceRigidBody(float radius, thomas::math::Vector3 center)
{
	m_rigidBody = thomas::object::GameObject::AddComponent<thomas::object::component::RigidBodyComponent>();
	m_rigidBody->SetCollider(new btSphereShape(radius));
	m_rigidBody->SetKinematic(true);
	m_frustrumCullingComponent->SetRadius(radius);
}

bool IslandObject::CheckDestory()
{
	return m_destroy;
}
