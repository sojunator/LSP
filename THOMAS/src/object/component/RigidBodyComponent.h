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
			public:
				RigidBodyComponent();
				void Start();
				void Update();
				void SetMass(float mass);
				float GetMass();
				void SetKinematic(bool kinematic);
				void SetCollider(btCollisionShape* collider);
			private:
				btRigidBody* m_rigidBody;
				btCollisionShape* m_collider;
				float m_mass;
			};
		}
	}
}