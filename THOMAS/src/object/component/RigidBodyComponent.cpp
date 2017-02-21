#include "RigidBodyComponent.h"

#include "../GameObject.h"
#include "../../utils/Math.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			void RigidBodyComponent::UpdateRigidbodyMass(float mass)
			{
				btVector3 inertia;
				getCollisionShape()->calculateLocalInertia(mass, inertia);
				setMassProps(mass, inertia);
				
			}
			RigidBodyComponent::RigidBodyComponent() : Component("RigidBodyComponent"), btRigidBody(1, NULL, NULL)
			{
			}

			RigidBodyComponent::~RigidBodyComponent()
			{
				Physics::s_world->removeRigidBody(this);
			}

			void RigidBodyComponent::Start()
			{
				btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(*(btQuaternion*)&m_gameObject->m_transform->GetRotation(), *(btVector3*)&m_gameObject->m_transform->GetPosition()));
				btCollisionShape* collider = new btBoxShape(btVector3(1, 1, 1));
				btVector3 inertia(0, 0, 0);
				collider->calculateLocalInertia(1, inertia);
				setMotionState(motionState);
				setCollisionShape(collider);
				setMassProps(1, inertia);
				Physics::s_world->addRigidBody(this);
				m_kinematic = false;
			}

			void RigidBodyComponent::Update()
			{
				//Update our transform to match the rigidbody.
				btTransform trans;
				btDefaultMotionState *myMotionState = (btDefaultMotionState *)getMotionState();
				trans = myMotionState->m_graphicsWorldTrans;
				math::Vector3 pos = (math::Vector3)trans.getOrigin();
				math::Quaternion rot = (math::Quaternion)trans.getRotation();
				m_gameObject->m_transform->SetRotation(rot);
				m_gameObject->m_transform->SetPosition(pos);
			}
			void RigidBodyComponent::SetKinematic(bool kinematic)
			{
				
				if (kinematic && !m_kinematic)
				{
					m_mass = -getInvMass();
					m_kinematic = kinematic;
					Physics::s_world->removeRigidBody(this);
					UpdateRigidbodyMass(0);
					Physics::s_world->addRigidBody(this);
				}
				else if(!kinematic && m_kinematic)
				{
					m_kinematic = kinematic;
					Physics::s_world->removeRigidBody(this);
					UpdateRigidbodyMass(m_mass);
					Physics::s_world->addRigidBody(this);
				}
		
			}
			bool RigidBodyComponent::IsKinematic()
			{
				return m_kinematic;
			}
			void RigidBodyComponent::SetCollider(btCollisionShape * collider)
			{
				Physics::s_world->removeRigidBody(this);
				setCollisionShape(collider);
				UpdateRigidbodyMass(m_mass);
				Physics::s_world->addRigidBody(this);
			}
			void RigidBodyComponent::SetMass(float mass)
			{
				Physics::s_world->removeRigidBody(this);
				m_mass = mass;
				UpdateRigidbodyMass(m_mass);
				Physics::s_world->addRigidBody(this);
			}
			float RigidBodyComponent::GetMass()
			{
				return m_mass;
			}
		}
	}
}

