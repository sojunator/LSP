#include "RigidBodyComponent.h"

#define _XM_NO_INTRINSICS_ 1;
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
				if (m_rigidBody)
				{
					btVector3 inertia(0, 0, 0);
					m_collider->calculateLocalInertia(mass, inertia);
					m_rigidBody->setMassProps(mass, inertia);
				}
			}
			RigidBodyComponent::RigidBodyComponent() : Component("RigidBodyComponent")
			{
				m_mass = 1;
			}

			void RigidBodyComponent::Start()
			{
				btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(*(btQuaternion*)&m_gameObject->m_transform->GetRotation(), *(btVector3*)&m_gameObject->m_transform->GetPosition()));
				m_collider = new btBoxShape(btVector3(1, 1, 1));
				btVector3 inertia(0, 0, 0);
				m_collider->calculateLocalInertia(m_mass, inertia);
				m_rigidBody = new btRigidBody(m_mass, motionState, m_collider, inertia);
				Physics::s_world->addRigidBody(m_rigidBody);
			}

			void RigidBodyComponent::Update()
			{
				//Update our transform to match the rigidbody.
				btTransform trans;
				m_rigidBody->getMotionState()->getWorldTransform(trans);
				math::Vector3 pos = (math::Vector3)trans.getOrigin();
				math::Quaternion rot = (math::Quaternion)trans.getRotation();
				m_gameObject->m_transform->SetRotation(rot);
				m_gameObject->m_transform->SetPosition(pos);
			}
			void RigidBodyComponent::SetMass(float mass)
			{
				m_mass = mass;
				UpdateRigidbodyMass(m_mass);
			}
			float RigidBodyComponent::GetMass()
			{
				return m_mass;
			}
			void RigidBodyComponent::SetKinematic(bool kinematic)
			{
				m_kinematic = kinematic;
				if (kinematic)
				{
					UpdateRigidbodyMass(0);
				}
				else
				{
					UpdateRigidbodyMass(m_mass);
				}
		
			}
			bool RigidBodyComponent::IsKinematic()
			{
				return m_kinematic;
			}
			void RigidBodyComponent::SetCollider(btCollisionShape * collider)
			{
				Physics::s_world->removeRigidBody(m_rigidBody);
				m_collider = collider;
				m_rigidBody->setCollisionShape(m_collider);
				SetMass(m_mass);
				Physics::s_world->addRigidBody(m_rigidBody);
			}
			btRigidBody * RigidBodyComponent::GetRigidBody()
			{
				return m_rigidBody;
			}
		}
	}
}

