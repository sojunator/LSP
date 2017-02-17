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

				btVector3 inertia(0, 0, 0);
				getCollisionShape()->calculateLocalInertia(mass, inertia);
				setMassProps(mass, inertia);
				
			}
			RigidBodyComponent::RigidBodyComponent() : Component("RigidBodyComponent"), btRigidBody(1, NULL, NULL)
			{
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
			}

			void RigidBodyComponent::Update()
			{
				//Update our transform to match the rigidbody.
				btTransform trans;
				getMotionState()->getWorldTransform(trans);
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
					UpdateRigidbodyMass(0);
				}
				else if(!kinematic && m_kinematic)
				{
					m_kinematic = kinematic;
					UpdateRigidbodyMass(m_mass);
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
				m_mass = mass;
				UpdateRigidbodyMass(m_mass);
			}
			float RigidBodyComponent::GetMass()
			{
				return m_mass;
			}
		}
	}
}

