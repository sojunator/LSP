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
				if (m_rigidBody)
				{
					btVector3 inertia(0, 0, 0);
					m_collider->calculateLocalInertia(m_mass, inertia);
					m_rigidBody->setMassProps(mass, inertia);
				}
					
			}
			float RigidBodyComponent::GetMass()
			{
				return m_mass;
			}
			void RigidBodyComponent::SetKinematic(bool kinematic)
			{
				if (kinematic)
				{
					m_rigidBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
					m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
				}
				else
				{
					m_rigidBody->setCollisionFlags(btCollisionObject::CF_ANISOTROPIC_FRICTION);
					m_rigidBody->setActivationState(ACTIVE_TAG);
				}
		
			}
			void RigidBodyComponent::SetCollider(btCollisionShape * collider)
			{
				m_collider = collider;
				m_rigidBody->setCollisionShape(m_collider);
				SetMass(m_mass);
			}
		}
	}
}

