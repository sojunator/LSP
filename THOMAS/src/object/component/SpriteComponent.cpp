#include "SpriteComponent.h"
#include "../../Window.h"
namespace thomas
{
	namespace object
	{
		namespace component
		{

			SpriteComponent::SpriteComponent(GameObject * gameObject) : Component("SpriteComponent", gameObject)
			{
			}

			math::Vector2 SpriteComponent::GetPosition()
			{
				return m_imagePos;
			}

			float SpriteComponent::GetScale()
			{
				return m_scale;
			}

			std::string SpriteComponent::GetSignature()
			{
				return m_name;
			}

			void SpriteComponent::SetName(std::string name)
			{
				m_name = name;
			}

			void SpriteComponent::SetPositionX(float posX)
			{
				m_imagePos.x = posX * Window::GetWidth();
			}

			void SpriteComponent::SetPositionY(float posY)
			{
				m_imagePos.y = posY * Window::GetHeight();
			}

			void SpriteComponent::SetScale(float scale)
			{
				m_scale = scale;
			}
		}
	}
}
