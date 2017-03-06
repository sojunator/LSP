#include "IslandObject.h"

IslandObject::~IslandObject()
{
}

void IslandObject::PlaceRigidBody()
{
	m_rigidBody = thomas::object::GameObject::AddComponent<thomas::object::component::RigidBodyComponent>();
	m_rigidBody->SetMass(0);
	m_rigidBody->SetCollider(new btSphereShape(m_islands->GetCollisionRadius(i)));
	m_rigidBody->setWorldTransform(btTransform(btQuaternion(), btVector3(m_islands->GetCenter(i).x, 0, m_islands->GetCenter(i).z)));
}
