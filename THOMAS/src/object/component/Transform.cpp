#include "Transform.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{
			Transform::Transform(GameObject* gameObject): Component("TransformComponent", gameObject)
			{
				m_localScale = math::Vector3::One;
				m_parent = NULL;
			}
			math::Vector3 Transform::Forward()
			{
				return math::Vector3::Transform(math::Vector3::Forward, m_localRotation);
			}
			math::Vector3 Transform::Up()
			{
				return math::Vector3::Transform(math::Vector3::Up, m_localRotation);
			}
			math::Vector3 Transform::Right()
			{
				return math::Vector3::Transform(math::Vector3::Right, m_localRotation);
			}

			math::Matrix Transform::GetLocalWorldMatrix()
			{
				return math::Matrix::CreateScale(m_localScale) * math::Matrix::CreateFromQuaternion(m_localRotation) * math::Matrix::CreateTranslation(m_localPosition);
			}

			math::Matrix Transform::GetWorldMatrix()
			{
				return math::Matrix::CreateScale(GetScale()) * math::Matrix::CreateFromQuaternion(GetRotation()) * math::Matrix::CreateTranslation(GetPosition());
			}

			void Transform::LookAt(Transform * target)
			{
				math::Vector3 relativePos = target->GetPosition() - GetPosition();
				relativePos.Normalize();
				m_localRotation = math::Quaternion::CreateFromYawPitchRoll(relativePos.x, relativePos.y, relativePos.z);
			}
			void Transform::Rotate(math::Vector3 angles)
			{
				math::Quaternion addedRotation = math::Quaternion::CreateFromYawPitchRoll(angles.x, angles.y, angles.z);

				m_localRotation *= addedRotation;
			}
			void Transform::Translate(math::Vector3 translation)
			{
				m_localPosition += translation;
			}
			Transform * Transform::GetParent()
			{
				return m_parent;
			}
			void Transform::SetParent(Transform * parent)
			{
				m_parent = parent;
			}
			math::Vector3 Transform::GetPosition()
			{
				if (m_parent)
					return m_parent->GetPosition()*m_localPosition;
				else
					return m_localPosition;
			}
			math::Quaternion Transform::GetRotation()
			{
				if (m_parent)
					return m_parent->GetRotation()*m_localRotation;
				else
					return m_localRotation;
			}
			math::Vector3 Transform::GetScale()
			{
				if (m_parent)
					return m_parent->GetScale()*m_localScale;
				else
					return m_localScale;
			}
			void Transform::SetPosition(math::Vector3 position)
			{
				if (m_parent)
					m_localPosition = position - m_parent->GetPosition();
				else
					m_localPosition = position;
			}
			void Transform::SetRotation(math::Quaternion rotation)
			{
				if (m_parent)
					m_localRotation = rotation - m_parent->GetRotation();
				else
					m_localRotation = rotation;
			}
			void Transform::SetScale(math::Vector3 scale)
			{
				if (m_parent)
					m_localScale = scale - m_parent->GetScale();
				else
					m_localScale = scale;
			}
		}
	}
}
