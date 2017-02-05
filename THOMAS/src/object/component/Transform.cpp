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
					return m_localWorldMatrix * m_parent->GetWorldMatrix();
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
				math::Quaternion rot = math::Quaternion::CreateFromYawPitchRoll(angles.x, angles.y, angles.z);
				math::Matrix newRot = math::Matrix::Transform(math::Matrix::CreateFromQuaternion(m_localRotation), rot);
				m_localWorldMatrix = math::Matrix::CreateScale(m_localScale) * math::Matrix::CreateWorld(m_localPosition, newRot.Forward(), newRot.Up());

				Decompose();
			}
			void Transform::Rotate(float x, float y, float z)
			{
				return Rotate(math::Vector3(x, y, z));
			}
			
			void Transform::Translate(math::Vector3 translation)
			{
				math::Matrix pos = math::Matrix::CreateTranslation(translation);
				
				m_localWorldMatrix *= pos;
				Decompose();
			}
			void Transform::Translate(float x, float y, float z)
			{
				return Translate(math::Vector3(x, y, z));
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
			void Transform::SetPosition(float x, float y, float z)
			{
				SetPosition(math::Vector3(x, y, z));
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
			void Transform::SetRotation(float yaw, float pitch, float roll)
			{
				SetRotation(math::Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll));
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
			void Transform::SetScale(float x, float y, float z)
			{
				return SetScale(math::Vector3(x, y, z));
			}
			void Transform::SetScale(float scale)
			{
				return SetScale(math::Vector3(scale, scale, scale));
			}
		}
	}
}
