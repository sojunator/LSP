#pragma once
#include "Component.h"
#include "../../Physics.h"
namespace thomas
{
	namespace object
	{
		namespace component
		{
			class THOMAS_API RigidBodyComponent : public Component
			{
			private:
				void UpdateRigidbodyMass(float mass);
			public:
				RigidBodyComponent();
				void Start();
				void Update();
				void SetMass(float mass);
				float GetMass();
				void SetKinematic(bool kinematic);
				bool IsKinematic();
				void SetCollider(btCollisionShape* collider);
				btRigidBody* GetRigidBody();
			private:
				btRigidBody* m_rigidBody;
				btCollisionShape* m_collider;
				float m_mass;
				bool m_kinematic;
			};
		}
	}
}