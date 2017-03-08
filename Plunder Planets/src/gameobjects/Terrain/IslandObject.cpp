#include "IslandObject.h"

thomas::object::component::SoundComponent* IslandObject::m_sound;

IslandObject::~IslandObject()
{
}

void IslandObject::Start()
{
	//m_frustrumCullingComponent = AddComponent<thomas::object::component::FrustumCullingComponent>();
	m_renderer = thomas::object::GameObject::AddComponent<thomas::object::component::RenderComponent>();
	m_sound = thomas::object::GameObject::AddComponent<thomas::object::component::SoundComponent>();
	m_sound->SetClip("fPlunder");
	m_sound->SetLooping(true);
	m_startY = -5;
	//m_transform->SetPosition(0, -5, 0);

	m_falling = false;
}

void IslandObject::Update()
{
	btVector3 posRigid = m_rigidBody->getWorldTransform().getOrigin();
	thomas::math::Vector3 posTran = m_transform->GetPosition();
	if (m_falling)
	{
		if (m_startY >= -800)
		{
			m_startY = m_startY - 9.82 * thomas::ThomasTime::GetDeltaTime();
			m_transform->SetPosition(0, m_startY, 0);
		}
	}
}

void IslandObject::Destroy()
{
}

void IslandObject::SetModel(int island)
{
	m_renderer->SetModel("Island-" + std::to_string(island));
}

void IslandObject::SinkIsland()
{
	if (!m_falling)
	{
		m_rigidBody->SetActive(false);
		m_falling = true;
	}
}

void IslandObject::Looting(bool gotLoot)
{
	if (gotLoot)
		m_sound->Play();
	else
		m_sound->Pause();
}

void IslandObject::PlaceRigidBody(float radius, thomas::math::Vector3 center)
{
	m_rigidBody = thomas::object::GameObject::AddComponent<thomas::object::component::RigidBodyComponent>();
	m_rigidBody->SetCollider(new btSphereShape(radius));
	m_rigidBody->SetKinematic(true);
	m_rigidBody->setWorldTransform(btTransform(btQuaternion(), btVector3(center.x, 0, center.z)));
	//m_frustrumCullingComponent->SetRadius(radius);
	//m_frustrumCullingComponent->SetPosition(center);
}
