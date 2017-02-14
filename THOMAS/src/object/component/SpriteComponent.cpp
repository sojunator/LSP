#include "SpriteComponent.h"
#include "../../Window.h"
#include "../../graphics/Sprite.h"

namespace thomas
{
	namespace object
	{
		namespace component
		{

			SpriteComponent::SpriteComponent() : Component("SpriteComponent")
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

			UINT SpriteComponent::GetWidth()
			{
				return thomas::graphics::Sprite::GetImageWidth();
			}

			UINT SpriteComponent::GetHeight()
			{
				return thomas::graphics::Sprite::GetImageHeight();
			}

			std::string SpriteComponent::GetSignature()
			{
				return m_name;
			}

			math::Vector4 SpriteComponent::GetColor()
			{
				return m_color;
			}

			void SpriteComponent::SetName(std::string name)
			{
				m_name = name;
			}

			void SpriteComponent::SetPositionX(float posX)
			{
				m_imagePos.x = posX;
			}

			void SpriteComponent::SetPositionY(float posY)
			{
				m_imagePos.y = posY;
			}

			void SpriteComponent::SetScale(float scale)
			{
				m_scale = scale;
			}
			void SpriteComponent::SetColor(math::Vector4 color)
			{
				m_color = color;
			}
		}
	}
}
