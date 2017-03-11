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
	m_sound->SetClip("fPlunder");
	m_sound->SetLooping(true);
	m_falling = false;
	m_destroy = false;
	m_pauseObj = nullptr;
	m_radius = 0;
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
	}
}

void IslandObject::Looting(bool gotLoot, thomas::math::Vector3 shipPos, thomas::object::component::ParticleEmitterComponent* goldEmitter)
{
	if (gotLoot && !m_pauseObj->GetPauseState())
	{
		goldEmitter->StartEmitting();
		m_sound->Play();
	}
	else
	{
		m_sound->Pause();
	}
}

void IslandObject::PlaceRigidBody(float radius, thomas::math::Vector3 center)
{
	m_rigidBody = thomas::object::GameObject::AddComponent<thomas::object::component::RigidBodyComponent>();
	m_rigidBody->SetCollider(new btSphereShape(radius));
	m_rigidBody->SetKinematic(true);
	m_frustrumCullingComponent->SetRadius(radius);
	m_radius = radius;
}

bool IslandObject::CheckDestory()
{
	return m_destroy;
}
