#include "Transform.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{

			void Transform::Decompose() {
				m_localWorldMatrix.Decompose(m_localScale, m_localRotation, m_localPosition);
			}

			Transform::Transform(GameObject* gameObject): Component("TransformComponent", gameObject)
			{
				Decompose();
				m_parent = NULL;
			}
			math::Vector3 Transform::Forward()
			{
				return m_localWorldMatrix.Forward();
			}
			math::Vector3 Transform::Up()
			{
				return m_localWorldMatrix.Up();
			}
			math::Vector3 Transform::Right()
			{
				return m_localWorldMatrix.Right();
			}

			math::Matrix Transform::GetLocalWorldMatrix()
			{
				return m_localWorldMatrix;
			}

			math::Matrix Transform::GetWorldMatrix()
			{
				if (m_parent)
					return m_parent->GetWorldMatrix() * m_localWorldMatrix;
				else
					return m_localWorldMatrix;
			}

			void Transform::LookAt(Transform * target)
			{
				if (target->GetPosition() == GetPosition())
					return;
				math::Matrix lookAt = math::Matrix::CreateLookAt(GetPosition(), target->GetPosition(), Up());

				lookAt = lookAt.Invert();
				
				m_localWorldMatrix = math::Matrix::CreateScale(m_localScale) * math::Matrix::CreateWorld(m_localPosition, lookAt.Forward(), lookAt.Up());

				Decompose();

			}
			void Transform::Rotate(math::Vector3 angles)
			{

				math::Matrix rot = math::Matrix::CreateFromYawPitchRoll(angles.x, angles.y, angles.z);
				m_localWorldMatrix *= rot;
				Decompose();
			}
			void Transform::Translate(math::Vector3 translation)
			{
				math::Matrix pos = math::Matrix::CreateTranslation(translation);
				
				m_localWorldMatrix *= pos;
				Decompose();
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
				math::Vector3 newPosition;
				if (m_parent)
					newPosition = position - m_parent->GetPosition();
				else
					newPosition = position;

				m_localWorldMatrix = math::Matrix::CreateScale(m_localScale) * math::Matrix::CreateWorld(newPosition, math::Vector3::Forward, math::Vector3::Up);
				Decompose();
			}
			void Transform::SetRotation(math::Quaternion rotation)
			{
				math::Quaternion newRotation;
				if (m_parent)
					newRotation = rotation - m_parent->GetRotation();
				else
					newRotation = rotation;

				math::Matrix rotMatrix = math::Matrix::CreateFromQuaternion(newRotation);

				m_localWorldMatrix = math::Matrix::CreateScale(m_localScale) * math::Matrix::CreateWorld(m_localPosition, rotMatrix.Forward(), rotMatrix.Up());
				Decompose();
			}
			void Transform::SetScale(math::Vector3 scale)
			{
				math::Vector3 newScale;
				if (m_parent)
					newScale = scale - m_parent->GetScale();
				else
					newScale = scale;
				m_localWorldMatrix = math::Matrix::CreateScale(newScale) * math::Matrix::CreateWorld(m_localPosition, Forward(), Up());
				Decompose();
			}
		}
	}
}
