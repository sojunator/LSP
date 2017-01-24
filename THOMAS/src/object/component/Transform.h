#pragma once
#include "Component.h"
#include "../../utils/Math.h"
namespace thomas
{
	namespace object
	{
		namespace component
		{
			class THOMAS_API Transform: public Component
			{
			private:
			public:

				math::Quaternion m_localRotation;
				math::Vector3 m_localPosition;
				math::Vector3 m_localScale;
				


				Transform(GameObject* gameObject);


				math::Vector3 Forward();
				math::Vector3 Up();
				math::Vector3 Right();

				math::Matrix GetLocalWorldMatrix();
				math::Matrix GetWorldMatrix();

				void LookAt(Transform* target);
				void Rotate(math::Vector3 angles);
				void Translate(math::Vector3 translation);

				Transform* GetParent();
				void SetParent(Transform* parent);

				math::Vector3 GetPosition();
				math::Quaternion GetRotation();
				math::Vector3 GetScale();
				
				void SetPosition(math::Vector3 position);
				void SetRotation(math::Quaternion rotation);
				void SetScale(math::Vector3 scale);

			private:
				Transform* m_parent;
			};
		}
	}
}